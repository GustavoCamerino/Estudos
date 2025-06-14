#include <stdio.h>  // Para printf, perror
#include <stdlib.h> // Para exit
#include <unistd.h> // Para fork, pipe, read, write, close

int main()
{
    int fd[2]; // fd[0] para leitura, fd[1] para escrita
    pid_t pid;

    // 1. Cria o pipe
    if (pipe(fd) == -1)
    {
        perror("Erro ao criar o pipe");
        exit(EXIT_FAILURE);
    }

    // 2. Chama fork()
    pid = fork();

    if (pid < 0)
    {
        // Erro ao criar o processo filho
        perror("Erro ao chamar fork()");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Este é o processo filho
        close(fd[0]); // O filho fecha a extremidade de leitura do pipe (não vai ler)

        printf("hello\n");
        fflush(stdout); // Garante que "hello" seja impresso imediatamente

        // O filho envia um byte para o pai sinalizando que terminou
        char sinal = 'x';
        if (write(fd[1], &sinal, 1) == -1)
        {
            perror("Filho: Erro ao escrever no pipe");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);       // O filho fecha a extremidade de escrita
        exit(EXIT_SUCCESS); // O filho termina
    }
    else
    {
        // Este é o processo pai
        close(fd[1]); // O pai fecha a extremidade de escrita do pipe (não vai escrever)

        // O pai tenta ler do pipe. Isso bloqueia o pai até que o filho escreva.
        char buffer;
        if (read(fd[0], &buffer, 1) == -1)
        {
            perror("Pai: Erro ao ler do pipe");
            exit(EXIT_FAILURE);
        }

        printf("goodbye\n");
        close(fd[0]); // O pai fecha a extremidade de leitura
        // O pai não chama wait() aqui, mas aguardou implicitamente o filho através do pipe
        exit(EXIT_SUCCESS);
    }

    return 0; // Este return não será alcançado, pois um dos processos sairá.
}