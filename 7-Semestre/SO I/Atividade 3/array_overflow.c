#include <stdio.h>
#include <stdlib.h> // Para malloc, free, exit

int main() {
    int *data;
    int size = 10; // Vamos alocar espaço para 10 inteiros

    printf("Alocando um array de %d inteiros com malloc...\n", size);

    // Aloca memória para 'size' inteiros
    data = (int *)malloc(size * sizeof(int));

    // Verifica se a alocação foi bem-sucedida
    if (data == NULL) {
        perror("Erro ao alocar memória");
        return EXIT_FAILURE;
    }

    printf("Memória alocada com sucesso. Endereço base: %p\n", (void *)data);

    // Inicializa o array dentro dos limites válidos
    for (int i = 0; i < size; i++) {
        data[i] = i * 10;
        printf("data[%d] = %d\n", i, data[i]);
    }

    printf("\nTentando acessar uma posição alem do limite (data[100])...\n");

    // TENTA ACESSAR ALÉM DO LIMITE ALOCADO
    // Esta é a linha que causará o erro de "acesso inválido" que o Valgrind detectará.
    int invalid_access_value = data[100]; // Tentando acessar a posição 101 (índice 100)

    printf("Valor acessado (inválido): %d (esta linha pode ou não ser alcançada, dependendo do sistema e otimizações)\n", invalid_access_value);

    // Libera a memória alocada
    printf("Liberando a memória alocada...\n");
    free(data);
    printf("Memória liberada. Programa finalizado.\n");

    return EXIT_SUCCESS;
}