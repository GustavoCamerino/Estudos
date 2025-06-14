/**
 * @file novoproc1.c
 * @author Gustavo Camerino
 * @brief   Executa o programa date
 * @version 0.1
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
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
        execlp("/bin/date", "minha-data", NULL);
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