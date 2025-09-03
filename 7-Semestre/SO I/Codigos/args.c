#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    printf("Pids: %d\n", getpid());
    if (rc == 0)
    {
        // Filho: executa comando passado na linha de comando
        execvp(argv[1], &argv[1]);
        printf("Exec falhou!\n"); // Só aparece se execvp falhar
        printf("Olá Mundo do Filho: %d\n", getpid());
    }
    else
    {
        printf("Olá Mundo do Pai: %d\n", getpid());
        wait(NULL);
    }

    return 0;
}
