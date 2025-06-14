/**
 * @file memcomp.c
 * @author Gustavo Camerino
 * @brief Exemplo de uso de memória compartilhada em C.
 * @version 0.1
 * @date 2024-09-10
 *
 * Este programa demonstra como criar e usar memória compartilhada entre processos
 * utilizando as funções `shm_open`, `mmap`, entre outras.
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * @brief Função principal que cria e escreve em uma memória compartilhada.
 *
 * A função cria um segmento de memória compartilhada com o nome "minha_mem_compartilhada"
 * e escreve a mensagem "ola, mundo" neste segmento.
 *
 * @return int Retorna 0 em caso de sucesso.
 */
int main()
{
    const char *nome = "minha_mem_compartilhada"; ///< Nome da memória compartilhada.
    const int SIZE = 4096;                        ///< Tamanho da memória compartilhada.
    char *msg = "ola, mundo";                     ///< Mensagem a ser escrita na memória compartilhada.
    int 
    // Cria a memória compartilhada
    int shm_fd = shm_open(nome, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("Erro ao criar memória compartilhada"); ///< Exibe uma mensagem de erro caso falhe a criação.
        exit(1);
    }

    // Configura o tamanho da memória compartilhada
    ftruncate(shm_fd, SIZE);

    // Mapeia a memória compartilhada
    void *ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("Erro ao mapear memória compartilhada"); ///< Exibe uma mensagem de erro caso o mapeamento falhe.
        exit(1);
    }

    // Escreve a mensagem na memória compartilhada
    sprintf(ptr, "%s", msg);

    return 0;
}

int serie_de_Collatz(int a)
{
    int count;
    int a= 7;
    while (a != 1)
    {
        if (a % 2 == 0)
        {
            a /= 2;
        }
        else
        {
            a = 3 * a + 1;
        }
        count = sprintf(ptr,"%d\n",a);
        ptr += count;
    }

}