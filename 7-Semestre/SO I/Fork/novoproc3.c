#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    // pid_t pid = fork();
    int pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork falhou!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        //  Filho executa o programa ls
        close(1); // Fecha a saída padrão
        open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        execlp("/bin/ls", "meu-ls", "-l", NULL);
        printf("Isso não será impresso\n");
    }
    else
    {
        //  Pai espera o filho terminar
        wait(NULL); //  Espera o filho terminar
        printf("Filho completou!\n");
    }

    return 0;
}