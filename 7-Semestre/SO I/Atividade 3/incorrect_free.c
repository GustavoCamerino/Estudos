#include <stdio.h>
#include <stdlib.h> // Para malloc, free, exit

int main() {
    int *ptr;
    int size = 5; // Vamos alocar espaço para 5 inteiros

    printf("Alocando um bloco de %d inteiros com malloc...\n", size);

    // Aloca memória para 'size' inteiros
    ptr = (int *)malloc(size * sizeof(int));

    // Verifica se a alocação foi bem-sucedida
    if (ptr == NULL) {
        perror("Erro ao alocar memória");
        return EXIT_FAILURE;
    }

    printf("Memória alocada com sucesso. Endereço original: %p\n", (void *)ptr);

    // Inicializa a memória (opcional, mas bom para simular uso)
    for (int i = 0; i < size; i++) {
        ptr[i] = i + 1;
    }
    printf("Memória inicializada.\n");

    // TENTANDO LIBERAR A MEMÓRIA COM UM PONTEIRO INVÁLIDO
    // Passamos 'ptr + 1', que não é o endereço exato retornado por malloc.
    // Isso causará um erro.
    printf("\nTentando liberar a memória com free(ptr + 1)...\n");
    free(ptr + 1); // ERRO: Ponteiro inválido para free()

    printf("O programa tentou liberar a memória (o erro pode ter ocorrido antes desta linha).\n");

    // Tentativa de liberar o ponteiro original (para evitar um vazamento de memória se o programa continuar)
    // No entanto, dependendo do erro anterior, esta linha pode causar um "double free"
    // ou outra falha, se o runtime C já estiver em um estado inconsistente.
    // Para ver o erro mais limpo, talvez você queira comentar esta linha.
    // Mas para fins de demonstração, podemos deixá-la para ver o que Valgrind reporta.
    // printf("Tentando liberar o ponteiro original com free(ptr)...\n");
    // free(ptr); // Isso pode ser um "double free" ou crash, dependendo do sistema

    printf("Programa finalizado.\n");

    return EXIT_SUCCESS;
}