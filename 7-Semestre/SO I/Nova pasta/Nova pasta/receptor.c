/**
 * @file memcomp.c
 * @author Gustavo Camerino
 * @brief Exemplo de uso de memória compartilhada em C (Leitura).
 * @version 0.1
 * @date 2024-09-10
 *
 * Este programa demonstra como abrir e ler um segmento de memória compartilhada
 * entre processos utilizando as funções `shm_open`, `mmap`, entre outras.
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

/**
 * @brief Função principal que abre e lê uma memória compartilhada.
 *
 * A função abre um segmento de memória compartilhada com o nome "minha_mem_compartilhada"
 * previamente criado e lê seu conteúdo, exibindo-o no terminal.
 *
 * @return int Retorna 0 em caso de sucesso.
 */
int main()
{
    const char *nome = "minha_mem_compartilhada"; ///< Nome da memória compartilhada.
    const int SIZE = 4096;                        ///< Tamanho da memória compartilhada.

    // Abre a memória compartilhada para leitura
    int shm_fd = shm_open(nome, O_RDONLY, 0666);
    if (shm_fd == -1)
    {
        perror("Erro ao abrir a memória compartilhada"); ///< Exibe uma mensagem de erro caso falhe a abertura.
        exit(1);
    }

    // Mapeia a memória compartilhada
    void *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("Erro ao mapear a memória compartilhada"); ///< Exibe uma mensagem de erro caso o mapeamento falhe.
        exit(1);
    }

    // Lê e exibe o conteúdo da memória compartilhada
    printf("%s\n", (char *)ptr);

    // Desfaz o mapeamento e a memória compartilhada
    shm_unlink(nome);

    return 0;
}
