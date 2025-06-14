/**
 * @file pipe.c
 * @author Gustavo Camerino de Carvalho
 * @brief  Exemplo de comunicação entre processos usando pipe e fork.
 * @version 0.1
 * @date 2024-09-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
/**
 * @brief Função principal que cria o pipe e realiza a comunicação entre pai e filho.
 *        A função cria um pipe e usa fork() para gerar um processo filho.
 *        O filho lê dados do pipe e o pai é responsável por enviar esses dados.
 *
 * @return int Retorna 0 em caso de sucesso.
 */
int main()
{
    int fd[2];
    int pid;
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        char buffer[20];
        close(fd[1]); //  Fecha o lado de escrita do pipe

        // Lê dados do pipe
        read(fd[0], buffer, sizeof(buffer)); // Lê os dados enviados pelo processo pai.
        printf("Filho leu: %s\n", buffer);   // Exibe a mensagem lida no pipe.

        close(fd[0]); // Fecha o lado de leitura do pipe após a leitura.
    }
    else
    {
        char *msg = "Oi, filhão!";
        close(fd[0]); // Fecha o lado de leitura do pipe

        //  Escreve no pipe
        write(fd[1], msg, strlen(msg) + 1);
        //  Fecha o lado de escrita do pipe
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}