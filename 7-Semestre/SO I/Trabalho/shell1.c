/*
Name        :   Kalpish Singhal
******************************************************************************
FUNCTIONALITIES IMPLEMENTED-
1. Execute all the External commands (ls, clear, vi etc.)
2. Implement Internal commands: cd, pwd
3. Print Initialize and use environment variables
4. Print environment variables using echo command
5. I/O redirection (<, >)
6. Support for history command and '!' operator (history, !!, !-1, !10, !-10 etc)
7. Pipes “|” (multiple) (Ex: ls | grep 'a' | wc)
8. Handle Interrupt Signal: On pressing "Ctrl+C", the command that is running
   currently should be terminated, your program should not terminate.
********************************************************************************
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>

/* GLOBAL VARIABLES */
int pipe_count = 0, fd;
static char *args[512];
char *history_file;
char input_buffer[1024];
char *cmd_exec[100];
int flag, len;
char cwd[1024];
int flag_pipe = 1;
pid_t pid;
int no_of_lines;
int environment_flag;
int flag_without_pipe, output_redirection, input_redirection;
int bang_flag;
char history_data[1000][1000];
char current_directory[1000];
char *input_redirection_file;
char *output_redirection_file;
extern char **environ;

/*************************** Function Declarations *****************************/
void clear_variables();
void file_process();
void file_write();
void bang_execute();
void environment();
void set_environment_variables();
void change_directory();
void print_current_directory();
void echo_calling(char *echo_val);
void history_execute_with_constants();
static char *skip_white(char *s);
void tokenize_commands(char *com_exec);
void tokenize_redirect_input_output(char *cmd_exec);
void tokenize_redirect_input(char *cmd_exec);
void tokenize_redirect_output(char *cmd_exec);
char *skip_comma(char *str);
static int split(char *cmd_exec, int input, int first, int last);
void with_pipe_execute();
static int command(int input, int first, int last, char *cmd_exec);
void prompt();
void sigintHandler(int sig_num);

/*************************************************************************/
void sigintHandler(int sig_num)
{
    signal(SIGINT, sigintHandler); // Reset signal handler
    fflush(stdout);
}

void clear_variables()
{
    fd = 0;
    flag = 0;
    len = 0;
    no_of_lines = 0;
    pipe_count = 0;
    flag_pipe = 0;
    flag_without_pipe = 0;
    output_redirection = 0;
    input_redirection = 0;
    input_buffer[0] = '\0';
    cwd[0] = '\0';
    pid = 0;
    environment_flag = 0;
    bang_flag = 0;
}

void file_process()
{
    int fd;
    history_file = (char *)malloc(100 * sizeof(char));
    strcpy(history_file, current_directory);
    strcat(history_file, "/history.txt");

    fd = open(history_file, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        perror("Failed to open history file");
        return;
    }

    int bytes_read = 0, x = 0;
    char buffer[1], temp_data[1000];
    do
    {
        bytes_read = read(fd, buffer, sizeof(buffer));
        for (int i = 0; i < bytes_read; ++i)
        {
            temp_data[x++] = buffer[i];
            if (buffer[i] == '\n')
            {
                temp_data[x - 1] = '\0'; // Replace newline with null terminator
                strcpy(history_data[no_of_lines++], temp_data);
                x = 0;               // Reset index for next line
                temp_data[0] = '\0'; // Reset temp_data
            }
        }
    } while (bytes_read == sizeof(buffer));
    close(fd);
}

void file_write()
{
    int fd_out;
    no_of_lines++;
    char input_data[2000];
    snprintf(input_data, sizeof(input_data), " %d %s\n", no_of_lines, input_buffer);

    fd_out = open(history_file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_out < 0)
    {
        perror("Error in writing file");
        return;
    }
    write(fd_out, input_data, strlen(input_data));
    close(fd_out);
}

void bang_execute()
{
    char bang_val[1000];
    char *tokenise_bang[100];
    int i, n = 1, num, index = 0;
    i = 1;
    if (input_buffer[i] == '!')
    {
        strcpy(bang_val, history_data[no_of_lines - 1]);
    }
    else if (input_buffer[i] == '-')
    {
        num = atoi(&input_buffer[++i]);
        index = no_of_lines - num;
        strcpy(bang_val, history_data[index]);
    }
    else
    {
        num = atoi(&input_buffer[i]);
        strcpy(bang_val, history_data[num - 1]);
    }

    tokenise_bang[0] = strtok(bang_val, " ");
    while ((tokenise_bang[n] = strtok(NULL, " ")) != NULL)
        n++;

    // Skip command name for input_buffer
    strcpy(input_buffer, tokenise_bang[1]);
    printf("%s\n", input_buffer);
}

void environment()
{
    char env_val[1000];
    strcpy(env_val, args[1]);
    char *value = getenv(env_val);

    if (value)
        printf("%s\n", value);
    else
        printf("\n");
}

void set_environment_variables()
{
    if (args[1] == NULL)
    {
        for (char **env = environ; *env != NULL; env++)
            printf("declare -x %s\n", *env);
        return;
    }

    char *key = strtok(args[1], "=");
    char *value = strtok(NULL, "=");
    setenv(key, value, 1); // 1 for overwrite
}

void change_directory()
{
    const char *home_dir = getenv("HOME");
    if (args[1] == NULL)
    {
        chdir(home_dir);
    }
    else if (chdir(args[1]) < 0)
    {
        perror("cd failed");
    }
}

void print_current_directory()
{
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
    }
}

void echo_calling(char *echo_val)
{
    char new_args[1024] = {0};
    char *str = strtok(echo_val, " ");
    if (!str)
    {
        printf("\n");
        return;
    }

    str = strtok(NULL, "");
    if (str)
    {
        strcpy(new_args, str);
        if (strchr(new_args, '$'))
        {
            environment();
        }
        else
        {
            printf("%s\n", new_args);
        }
    }
}

void history_execute_with_constants()
{
    if (bang_flag == 1)
    {
        for (int i = 0; i < no_of_lines; i++)
            printf("%s\n", history_data[i]);
    }
    else
    {
        int num = (args[1] != NULL) ? atoi(args[1]) : no_of_lines;
        int start_index = (num > no_of_lines) ? 0 : no_of_lines - num;
        for (int i = start_index; i < no_of_lines; i++)
            printf("%s\n", history_data[i]);
    }
}

static char *skip_white(char *s)
{
    while (isspace(*s))
        ++s;
    return s;
}

void tokenize_commands(char *com_exec)
{
    int m = 0;
    args[m++] = strtok(com_exec, " ");
    while ((args[m++] = strtok(NULL, " ")) != NULL)
        ;
}

void tokenize_redirect_input_output(char *cmd_exec)
{
    char *io_token[3];
    io_token[0] = strtok(cmd_exec, "<");
    io_token[1] = strtok(NULL, ">");

    input_redirection_file = skip_white(io_token[1]);
    output_redirection_file = skip_white(io_token[2]);

    tokenize_commands(io_token[0]);
}

void tokenize_redirect_input(char *cmd_exec)
{
    char *i_token[2];
    i_token[0] = strtok(cmd_exec, "<");

    input_redirection_file = skip_white(strtok(NULL, "<"));
    tokenize_commands(i_token[0]);
}

void tokenize_redirect_output(char *cmd_exec)
{
    char *o_token[2];
    o_token[0] = strtok(cmd_exec, ">");

    output_redirection_file = skip_white(strtok(NULL, ">"));
    tokenize_commands(o_token[0]);
}

char *skip_comma(char *str)
{
    char temp[1000];
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != '"')
            temp[j++] = str[i];
    }
    temp[j] = '\0';
    return strdup(temp);
}

static int split(char *cmd_exec, int input, int first, int last)
{
    char *command_array[50];
    int pipe_count = 0;

    while (1)
    {
        if (cmd_exec[0] == '\0')
            break;
        command_array[pipe_count++] = strtok(cmd_exec, "|");
        cmd_exec = NULL;
    }

    for (int i = 0; i < pipe_count; i++)
    {
        command(input, i, pipe_count - 1, command_array[i]);
    }

    return pipe_count;
}

void with_pipe_execute()
{
    char *cmd_exec[10] = {NULL};
    int input = 0;
    cmd_exec[0] = input_buffer;

    pipe_count = split(cmd_exec[0], input, 0, pipe_count);
}

static int command(int input, int first, int last, char *cmd_exec)
{
    char *temp = cmd_exec;
    if (strchr(cmd_exec, '>'))
    {
        tokenize_redirect_output(temp);
        flag_without_pipe = 0;
        if (output_redirection_file)
            flag_without_pipe = 1;
    }
    else if (strchr(cmd_exec, '<'))
    {
        tokenize_redirect_input(temp);
        flag_without_pipe = 0;
        if (input_redirection_file)
            flag_without_pipe = 1;
    }
    else
    {
        flag_without_pipe = 1;
    }

    if (flag_without_pipe)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            return -1;
        }
        else if (pid == 0)
        {
            if (input_redirection_file)
            {
                int fd_in = open(input_redirection_file, O_RDONLY);
                if (fd_in < 0)
                {
                    perror("Input redirection failed");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }

            if (output_redirection_file)
            {
                int fd_out = open(output_redirection_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                if (fd_out < 0)
                {
                    perror("Output redirection failed");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }

            execvp(args[0], args);
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }
    }
    return 0;
}

void prompt()
{
    printf("Your Shell > ");
}

int main()
{
    signal(SIGINT, sigintHandler); // Set signal handler for Ctrl+C
    file_process();
    clear_variables();

    while (1)
    {
        prompt();
        fgets(input_buffer, sizeof(input_buffer), stdin);

        if (strlen(input_buffer) == 0)
            continue;

        input_buffer[strcspn(input_buffer, "\n")] = '\0'; // Remove newline character

        file_write();
        bang_flag = 0;

        // Handle history commands
        if (input_buffer[0] == '!')
        {
            bang_flag = 1;
            bang_execute();
        }

        if (strcmp(input_buffer, "exit") == 0)
            break;

        if (strchr(input_buffer, '|'))
        {
            with_pipe_execute();
        }
        else
        {
            tokenize_commands(input_buffer);
            if (strcmp(args[0], "cd") == 0)
                change_directory();
            else if (strcmp(args[0], "pwd") == 0)
                print_current_directory();
            else if (strcmp(args[0], "echo") == 0)
                echo_calling(input_buffer);
            else if (strcmp(args[0], "history") == 0)
                history_execute_with_constants();
            else if (strcmp(args[0], "set") == 0)
                set_environment_variables();
            else if (strcmp(args[0], "get") == 0)
                environment();
            else
            {
                pid = fork();
                if (pid == -1)
                {
                    perror("Fork failed");
                }
                else if (pid == 0)
                {
                    execvp(args[0], args);
                    perror("Command execution failed");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    wait(NULL);
                }
            }
        }
    }

    return 0;
}
