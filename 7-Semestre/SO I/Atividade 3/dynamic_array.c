#include <stdio.h>
#include <stdlib.h> // Para malloc, realloc, free, exit

// Definindo a capacidade inicial e o fator de crescimento
#define INITIAL_CAPACITY 4
#define RESIZE_FACTOR    2

// Estrutura para representar o vetor dinâmico
typedef struct {
    int *data;      // Ponteiro para o array de inteiros
    int size;       // Número atual de elementos no array
    int capacity;   // Capacidade máxima atual do array
} DynamicArray;

// --- Funções para o Vetor Dinâmico ---

// Inicializa um novo vetor dinâmico
DynamicArray* createDynamicArray() {
    DynamicArray *arr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (arr == NULL) {
        perror("Erro ao alocar DynamicArray");
        exit(EXIT_FAILURE);
    }

    arr->data = (int *)malloc(sizeof(int) * INITIAL_CAPACITY);
    if (arr->data == NULL) {
        perror("Erro ao alocar dados iniciais do array");
        free(arr); // Libera a própria estrutura se a alocação de dados falhar
        exit(EXIT_FAILURE);
    }

    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    printf("Vetor dinâmico criado com capacidade inicial: %d\n", arr->capacity);
    return arr;
}

// Expande a capacidade do vetor dinâmico
void expandDynamicArray(DynamicArray *arr) {
    int new_capacity = arr->capacity * RESIZE_FACTOR;
    printf("Vetor cheio. Expandindo de %d para %d elementos...\n", arr->capacity, new_capacity);

    int *new_data = (int *)realloc(arr->data, sizeof(int) * new_capacity);
    if (new_data == NULL) {
        perror("Erro ao reexpandir o array (realloc)");
        // Em caso de falha de realloc, os dados originais (arr->data) ainda são válidos.
        // O ideal seria tentar lidar com isso de forma mais robusta, mas para um exemplo,
        // sair é aceitável.
        free(arr->data); // Libera a memória original para evitar vazamento
        free(arr);       // Libera a estrutura
        exit(EXIT_FAILURE);
    }

    arr->data = new_data;
    arr->capacity = new_capacity;
    printf("Vetor expandido com sucesso. Nova capacidade: %d\n", arr->capacity);
}

// Adiciona um elemento ao vetor dinâmico
void addElement(DynamicArray *arr, int element) {
    // Verifica se há espaço. Se não houver, expande.
    if (arr->size == arr->capacity) {
        expandDynamicArray(arr);
    }

    arr->data[arr->size] = element;
    printf("Adicionado elemento %d na posição %d. Tamanho atual: %d/%d\n",
           element, arr->size, arr->size + 1, arr->capacity);
    arr->size++;
}

// Imprime os elementos do vetor dinâmico
void printDynamicArray(const DynamicArray *arr) {
    printf("\nElementos do Vetor Dinâmico (%d/%d): [", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Libera toda a memória alocada pelo vetor dinâmico
void destroyDynamicArray(DynamicArray *arr) {
    if (arr == NULL) return;
    free(arr->data); // Libera o array de dados
    free(arr);       // Libera a estrutura do vetor
    printf("\nVetor dinâmico e memória liberados.\n");
}

// --- Função Principal ---
int main() {
    DynamicArray *myArray = createDynamicArray();

    // Adiciona alguns elementos, forçando a expansão
    for (int i = 0; i < 15; i++) {
        addElement(myArray, i * 10 + 5);
        // Opcional: printar o array a cada adição para ver a expansão
        // printDynamicArray(myArray);
    }

    printDynamicArray(myArray);

    // Adiciona mais alguns elementos para forçar mais expansões
    for (int i = 15; i < 25; i++) {
        addElement(myArray, i * 10 + 5);
    }

    printDynamicArray(myArray);

    destroyDynamicArray(myArray);

    return EXIT_SUCCESS;
}