#include <stdio.h>    // Para printf, perror
#include <stdlib.h>   // Para exit, getenv
#include <unistd.h>   // Para fork, exec* funções
#include <sys/wait.h> // Para wait

// Função auxiliar para executar e aguardar o processo filho
void execute_and_wait(const char *exec_type, void (*exec_func)(), pid_t parent_pid)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Erro ao chamar fork()");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Processo Filho
        printf("\n--- Processo Filho (PID: %d) executando %s ---\n", getpid(), exec_type);
        exec_func(); // Chama a função exec específica
        // Se exec_func retornar, houve um erro
        perror("Erro na chamada exec");
        exit(EXIT_FAILURE); // O filho sai com erro
    }
    else
    {
        // Processo Pai
        int status;
        printf("Pai (PID: %d): Esperando pelo filho %d (%s)...\n", parent_pid, pid, exec_type);
        waitpid(pid, &status, 0); // Aguarda o filho terminar
        if (WIFEXITED(status))
        {
            printf("Pai (PID: %d): Filho %d (%s) terminou com status %d.\n",
                   parent_pid, pid, exec_type, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Pai (PID: %d): Filho %d (%s) terminou devido ao sinal %d.\n",
                   parent_pid, pid, exec_type, WTERMSIG(status));
        }
    }
}

// Funções para cada variante de exec()
void call_execl()
{
    // execl(path, arg0, arg1, ..., (char *)0)
    // path: Caminho absoluto para o executável
    // arg0: Nome do programa (geralmente o mesmo que o último componente de path)
    // arg1...: Argumentos para o programa, terminados por (char *)0
    execl("/bin/ls", "ls", "-l", "-a", (char *)NULL);
}

void call_execle()
{
    // execle(path, arg0, ..., (char *)0, envp[])
    // Semelhante a execl, mas permite especificar o ambiente.
    char *envp[] = {"MY_VAR=hello_from_execle", "PATH=/bin:/usr/bin", NULL};
    execle("/bin/ls", "ls", "-l", "-a", (char *)NULL, envp);
}

void call_execlp()
{
    // execlp(file, arg0, ..., (char *)0)
    // file: Nome do arquivo (o PATH será usado para encontrá-lo)
    // arg0...: Argumentos para o programa
    execlp("ls", "ls", "-l", "-a", (char *)NULL);
}

void call_execv()
{
    // execv(path, argv[])
    // path: Caminho absoluto
    // argv[]: Array de strings para os argumentos, o último elemento deve ser NULL
    char *argv[] = {"ls", "-l", "-a", NULL};
    execv("/bin/ls", argv);
}

void call_execvp()
{
    // execvp(file, argv[])
    // file: Nome do arquivo (o PATH será usado para encontrá-lo)
    // argv[]: Array de strings para os argumentos
    char *argv[] = {"ls", "-l", "-a", NULL};
    execvp("ls", argv);
}

void call_execvpe()
{
    // execvpe(file, argv[], envp[])
    // file: Nome do arquivo (o PATH será usado para encontrá-lo)
    // argv[]: Array de strings para os argumentos
    // envp[]: Array de strings para o ambiente
    char *argv[] = {"ls", "-l", "-a", NULL};
    char *envp[] = {"MY_VAR=hello_from_execvpe", "PATH=/bin:/usr/bin", NULL};
    execvpe("ls", argv, envp);
}

int main()
{
    pid_t parent_pid = getpid();
    printf("Processo Pai principal (PID: %d)\n", parent_pid);

    execute_and_wait("execl", call_execl, parent_pid);
    execute_and_wait("execle", call_execle, parent_pid);
    execute_and_wait("execlp", call_execlp, parent_pid);
    execute_and_wait("execv", call_execv, parent_pid);
    execute_and_wait("execvp", call_execvp, parent_pid);
    execute_and_wait("execvpe", call_execvpe, parent_pid);

    printf("\nProcesso Pai (PID: %d): Todas as variantes de exec() foram testadas.\n", parent_pid);

    return 0;
}