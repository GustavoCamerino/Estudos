#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_CMD_LEN 1024
#define MAX_ARG_LEN 100
#define PATH_LEN 1024

char *path_var = NULL; // variável global para armazenar o caminho

void execute_command(char *cmd);
void change_directory(char *path);
void print_working_directory();
void set_path_variable(char *new_path);
void print_path_variable();
void execute_pipe(char *cmd1, char *cmd2);
void compile_and_execute(char *prog_name);
char *expand_variables(char *cmd);

int main()
{

    int width = 50; // Largura do caminho
    int i;

    // Movimento para a direita
    for (i = 0; i < width; i++)
    {
        printf("\033[H\033[J");
        for (int j = 0; j < i; j++)
            printf(" ");
        printf("🚗");
        usleep(100000);
        fflush(stdout);
    }

    // Movimento de volta para a esquerda
    for (i = width; i >= 0; i--)
    {
        printf("\033[H\033[J");
        for (int j = 0; j < i; j++)
            printf(" ");
        printf("🚗");
        usleep(100000);
        fflush(stdout);
    }
    printf("\n");
    char cmd[MAX_CMD_LEN];
    printf("#-------------------------------------------------------------------------------------------------------------------------------# \n");
    printf("▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖    ▗▄▄▄▖▗▄▖      ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖ ▗▄▖  ▗▄▄▖     ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   \n");
    printf("▐▌ ▐▌▐▌   ▐▌   ▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌         █ ▐▌ ▐▌    ▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌   ▐▌ ▐▌  █  ▐▛▚▖▐▌▐▌ ▐▌▐▌       ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌   \n");
    printf("▐▌ ▐▌▐▛▀▀▘▐▌   ▐▌   ▐▌ ▐▌▐▌  ▐▌▐▛▀▀▘      █ ▐▌ ▐▌    ▐▌   ▐▛▀▜▌▐▌  ▐▌▐▛▀▀▘▐▛▀▚▖  █  ▐▌ ▝▜▌▐▌ ▐▌ ▝▀▚▖     ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   \n");
    printf("▐▙█▟▌▐▙▄▄▖▐▙▄▄▖▝▚▄▄▖▝▚▄▞▘▐▌  ▐▌▐▙▄▄▖      █ ▝▚▄▞▘    ▝▚▄▄▖▐▌ ▐▌▐▌  ▐▌▐▙▄▄▖▐▌ ▐▌▗▄█▄▖▐▌  ▐▌▝▚▄▞▘▗▄▄▞▘    ▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖\n");
    printf("#-------------------------------------------------------------------------------------------------------------------------------# \n");
    while (1)
    {
        printf("shell> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            break; // Sai se a leitura falhar
        }

        // Remove nova linha
        cmd[strcspn(cmd, "\n")] = 0;

        // Expande variáveis
        char *expanded_cmd = expand_variables(cmd);

        // Verifica se há pipe
        if (strstr(expanded_cmd, "|") != NULL)
        {
            char *cmd1 = strtok(expanded_cmd, "|");
            char *cmd2 = strtok(NULL, "|");
            execute_pipe(cmd1, cmd2);
        }
        else
        {
            execute_command(expanded_cmd);
        }

        free(expanded_cmd); // Libera a memória do comando expandido
    }

    return 0;
}

void execute_command(char *cmd)
{
    char *args[MAX_ARG_LEN];
    char *token = strtok(cmd, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARG_LEN - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    // Comando interno
    if (strcmp(args[0], "cd") == 0)
    {
        change_directory(args[1]);
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        print_working_directory();
    }
    else if (strcmp(args[0], "CAMINHO") == 0) // Acesso à variável CAMINHO
    {
        print_path_variable();
    }
    else if (strcmp(args[0], "export") == 0 && args[1] != NULL) // Define a variável CAMINHO
    {
        set_path_variable(args[1]);
    }
    else
    {
        // Comando externo
        pid_t pid = fork();
        if (pid == 0)
        {
            // Filha: executa o comando
            execvp(args[0], args);
            // Se execvp falhar
            printf("comando não encontrado\n");
            exit(1);
        }
        else if (pid > 0)
        {
            // Pai: espera o filho terminar
            wait(NULL);
        }
        else
        {
            perror("fork");
        }
    }
}

void change_directory(char *path)
{
    if (path == NULL || chdir(path) != 0)
    {
        perror("cd");
    }
}

void print_working_directory()
{
    char cwd[PATH_LEN];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("getcwd");
    }
}

void set_path_variable(char *new_path)
{
    if (path_var != NULL)
    {
        free(path_var);
    }
    path_var = strdup(new_path);
}

void print_path_variable()
{
    if (path_var != NULL)
    {
        printf("%s\n", path_var);
    }
    else
    {
        printf("CAMINHO não definido.\n");
    }
}

void execute_pipe(char *cmd1, char *cmd2)
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        // Filha 1: executa o primeiro comando
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        char *args1[MAX_ARG_LEN];
        char *token = strtok(cmd1, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARG_LEN - 1)
        {
            args1[i++] = token;
            token = strtok(NULL, " ");
        }
        args1[i] = NULL;
        execvp(args1[0], args1);
        printf("comando não encontrado\n");
        exit(1);
    }
    else if (pid1 > 0)
    {
        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            // Filha 2: executa o segundo comando
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            char *args2[MAX_ARG_LEN];
            char *token = strtok(cmd2, " ");
            int i = 0;
            while (token != NULL && i < MAX_ARG_LEN - 1)
            {
                args2[i++] = token;
                token = strtok(NULL, " ");
            }
            args2[i] = NULL;
            execvp(args2[0], args2);
            printf("comando não encontrado\n");
            exit(1);
        }
        else if (pid2 > 0)
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            wait(NULL);
            wait(NULL);
        }
        else
        {
            perror("fork");
        }
    }
    else
    {
        perror("fork");
    }
}

char *expand_variables(char *cmd)
{
    char *expanded_cmd = malloc(MAX_CMD_LEN);
    char *ptr = cmd;
    char *var_name_start;
    char *var_name;
    int i = 0;

    while (*ptr)
    {
        if (*ptr == '$')
        {
            ptr++;
            var_name_start = ptr;
            while (*ptr && (*ptr != ' ' && *ptr != '\n'))
            {
                ptr++;
            }
            var_name = strndup(var_name_start, ptr - var_name_start);
            if (strcmp(var_name, "caminho") == 0) // Substitui pela variável definida
            {
                if (path_var != NULL)
                {
                    strcpy(&expanded_cmd[i], path_var);
                    i += strlen(path_var);
                }
            }
            free(var_name);
        }
        else
        {
            expanded_cmd[i++] = *ptr++;
        }
    }
    expanded_cmd[i] = '\0';
    return expanded_cmd;
}

void compile_and_execute(char *prog_name)
{
    char prog_bin[PATH_LEN];
    snprintf(prog_bin, sizeof(prog_bin), "./%s", prog_name);
    FILE *file = fopen(prog_bin, "r");

    // Verifica se o programa binário existe
    if (file)
    {
        fclose(file);
        // Verifica se o arquivo C é mais recente
        struct stat stat_c, stat_bin;
        char prog_c[PATH_LEN];
        snprintf(prog_c, sizeof(prog_c), "%s.c", prog_name);
        if (stat(prog_c, &stat_c) == 0 && stat(prog_bin, &stat_bin) == 0)
        {
            if (difftime(stat_c.st_mtime, stat_bin.st_mtime) > 0)
            {
                // Compila o programa
                char compile_cmd[MAX_CMD_LEN];
                snprintf(compile_cmd, sizeof(compile_cmd), "gcc %s.c -o %s", prog_name, prog_name);
                system(compile_cmd);
            }
        }
        // Executa o programa
        system(prog_bin);
    }
    else
    {
        // Compila e executa
        char compile_cmd[MAX_CMD_LEN];
        snprintf(compile_cmd, sizeof(compile_cmd), "gcc %s.c -o %s", prog_name, prog_name);
        system(compile_cmd);
        system(prog_bin);
    }
}
