/**
 * @file comp.c
 * @author Gustavo Camerino de Carvalho
 * @brief
 * @version 0.1
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

// Executa o programa ls

int main()
{
    int pid = fork();
    int status;
    if (pid < 0)
    {
        fprintf(stderr, "Fork falhou\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // filho. Compila o programa olamundo.c
        //  execlp("/bin/ls", "meu-ls", "-l", NULL);
        execlp("gcc", "gcc", "olamundo.c", "-o", "olamundo", NULL);
    }
    else
    {
        // pai
        wait(&status); // espera o filho terminar
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            //  O filho compilou com sucesso!
            //  Executar o programa olamundo
            execlp("./olamundo", "olamundo", NULL);
    }
    exit(0);
}
