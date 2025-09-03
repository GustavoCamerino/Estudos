#include <stdio.h>
#include <stdlib.h> // Para malloc, free, exit

int main() {
    int *ptr;
    int size = 5; // Alocaremos espaço para 5 inteiros

    printf("Alocando um bloco de %d inteiros com malloc...\n", size);

    // Aloca memória para 'size' inteiros
    ptr = (int *)malloc(size * sizeof(int));

    // Verifica se a alocação foi bem-sucedida
    if (ptr == NULL) {
        perror("Erro ao alocar memória");
        return EXIT_FAILURE;
    }

    printf("Memória alocada com sucesso. Endereço: %p\n", (void *)ptr);

    // Inicializa e usa a memória alocada
    for (int i = 0; i < size; i++) {
        ptr[i] = i * 100;
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }

    printf("\nLiberando a memória com free()...\n");
    free(ptr); // A memória apontada por 'ptr' é agora liberada.
               // 'ptr' ainda mantém o endereço, mas o conteúdo é inválido.
    printf("Memória liberada. O ponteiro 'ptr' agora é um ponteiro 'dangling' (pendente).\n");

    // TENTANDO ACESSAR A MEMÓRIA APÓS ELA TER SIDO LIBERADA
    // Este é o erro "use-after-free"
    printf("\nTentando acessar a memória APOS ELA TER SIDO LIBERADA (ptr[0])...\n");
    int value_after_free = ptr[0]; // Comportamento indefinido! Pode travar ou retornar lixo.

    printf("Valor acessado após free: %d\n", value_after_free);

    // Observação: Não chame free(ptr) novamente, isso seria um "double free"
    // e Valgrind também o detectaria.

    printf("Programa finalizado.\n");

    return EXIT_SUCCESS;
}