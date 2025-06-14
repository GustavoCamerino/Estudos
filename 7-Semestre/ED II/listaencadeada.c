/**
 * @file lista_duplamente_encadeada.h
 * @brief Implementação de uma Lista Duplamente Encadeada
 * @author Gustavo Camerino de Carvalho
 * @date 2025-06-06
 */

#include <stdio.h>

/**
 * @struct No
 * @brief Estrutura que representa um nó da lista duplamente encadeada
 */
typedef struct No {
    int dado;      /**< Valor armazenado no nó */
    No *proximo;   /**< Ponteiro para o próximo nó */
    No *anterior;  /**< Ponteiro para o nó anterior */
} No;

/**
 * @struct listaDe
 * @brief Estrutura que representa a lista duplamente encadeada
 */
typedef struct listaDe {
    No *inicio;    /**< Ponteiro para o primeiro nó da lista */
    No *fim;       /**< Ponteiro para o último nó da lista */
} listaDe;

/**
 * @brief Cria um novo nó com o dado fornecido
 * @param dado Valor a ser armazenado no novo nó
 * @return Ponteiro para o novo nó criado
 * @throws Encerra o programa se houver falha na alocação de memória
 */
No *criaNo(int dado) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("[ERRO AO ALOCAR MEMÓRIA PARA O NOVO NÓ!]\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

/**
 * @brief Inicializa uma lista vazia
 * @param lista Ponteiro para a lista a ser inicializada
 */
void InicializaLista(listaDe *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

/**
 * @brief Verifica se a lista está vazia
 * @param lista Ponteiro para a lista a ser verificada
 * @return 1 se a lista estiver vazia, 0 caso contrário
 */
int estaVazia(listaDe *lista) {
    return lista->inicio == NULL;
}

/**
 * @brief Insere um novo nó no início da lista
 * @param lista Ponteiro para a lista onde será feita a inserção
 * @param dado Valor a ser inserido na lista
 */
void InsereNoInicio(listaDe *lista, int dado) {
    No *novoNo = criaNo(dado);
    if (estaVazia(lista)) {
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        novoNo->proximo = lista->inicio;
        lista->inicio->anterior = novoNo->proximo;
        lista->inicio = novoNo;
    }
    printf("Dado inserido na lista: %d\n", dado);
}

/**
 * @brief Insere um novo nó no fim da lista
 * @param lista Ponteiro para a lista onde será feita a inserção
 * @param dado Valor a ser inserido na lista
 */
void InsereNoFim(listaDe *lista, int dado) {
    No *novoNo = criaNo(dado);
    if (estaVazia(lista)) {
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        lista->fim->proximo = novoNo->anterior;
        novoNo->anterior = lista->fim;
        lista->fim = novoNo;
    }
}