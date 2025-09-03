/**
 * @file arvore_binaria.c
 * @brief Implementação de uma Árvore Binária de Busca com visualização hierárquica e altura dos nós.
 *
 * Este código implementa uma estrutura de árvore binária que armazena strings, com inserção,
 * busca e visualização formatada. Cada nó mantém sua altura para futuras possíveis extensões,
 * como balanceamento AVL.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct No
 * @brief Estrutura que representa um nó da árvore binária.
 */
typedef struct No
{
    char str[250];  /**< String armazenada no nó */
    struct No *esq; /**< Ponteiro para o filho à esquerda */
    struct No *dir; /**< Ponteiro para o filho à direita */
    int altura;     /**< Altura do nó na árvore */
} No;

// ==== Protótipos ====

No *CriaNo(const char *str);
No *InsereNo(No *raiz, const char *str);
No *BuscaNo(No *raiz, const char *str);
void printBonito(No *raiz, int nivel);
int altura(No *no);
int max(int a, int b);

// ==== Função principal ====

/**
 * @brief Função principal que testa a árvore com inserções e imprime sua estrutura.
 */
int main()
{
    No *raiz = NULL;
    raiz = InsereNo(raiz, "manga");
    raiz = InsereNo(raiz, "abacaxi");
    raiz = InsereNo(raiz, "banana");
    raiz = InsereNo(raiz, "carambola");
    raiz = InsereNo(raiz, "laranja");
    raiz = InsereNo(raiz, "uva");

    printf("\n🌲 Árvore Binária:\n\n");
    printBonito(raiz, 0);

    return 0;
}

// ==== Implementações ====

/**
 * @brief Cria um novo nó com a string fornecida.
 *
 * @param str String a ser armazenada.
 * @return Ponteiro para o novo nó criado.
 */
No *CriaNo(const char *str)
{
    if (str == NULL || strlen(str) == 0)
    {
        printf("[ERRO, IMPOSSÍVEL REALIZAR TAL AÇÃO POIS \nO VALOR DA STRING É NULO\n]");
        exit(1);
    }

    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro de alocação de memória\n");
        exit(1);
    }

    strcpy(novoNo->str, str);
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 1; // Considerando altura inicial como 1 (folha)
    return novoNo;
}

/**
 * @brief Insere uma string na árvore binária de forma ordenada.
 *
 * @param raiz Ponteiro para a raiz atual da árvore.
 * @param str String a ser inserida.
 * @return Ponteiro para a nova raiz após a inserção.
 */
No *InsereNo(No *raiz, const char *str)
{
    if (raiz == NULL)
    {
        No *novoNo = CriaNo(str);
        printf("-- Inserindo %s na raiz como novo nó\n", str);
        return novoNo;
    }

    int cmp = strcmp(str, raiz->str);

    if (cmp < 0)
    {
        raiz->esq = InsereNo(raiz->esq, str);
        printf("-- Inserindo %s à esquerda\n", str);
    }
    else if (cmp > 0)
    {
        raiz->dir = InsereNo(raiz->dir, str);
        printf("-- Inserindo %s à direita\n", str);
    }
    else
    {
        printf("-- Valor %s já existe na árvore\n", str);
    }

    // Atualiza a altura após inserção
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
    return raiz;
}

/**
 * @brief Busca uma string na árvore binária.
 *
 * @param raiz Ponteiro para a raiz da árvore.
 * @param str String a ser buscada.
 * @return Ponteiro para o nó que contém a string, ou NULL se não encontrado.
 */
No *BuscaNo(No *raiz, const char *str)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    int cmp = strcmp(str, raiz->str);

    if (cmp == 0)
    {
        return raiz;
    }
    else if (cmp < 0)
    {
        return BuscaNo(raiz->esq, str);
    }
    else
    {
        return BuscaNo(raiz->dir, str);
    }
}

/**
 * @brief Imprime a árvore de forma hierárquica e visualmente organizada.
 *
 * @param raiz Ponteiro para a raiz da árvore.
 * @param nivel Nível atual de profundidade (usado para indentação).
 */
void printBonito(No *raiz, int nivel)
{
    if (raiz == NULL)
        return;

    printBonito(raiz->dir, nivel + 1);

    for (int i = 0; i < nivel; i++)
        printf("       ");

    printf("└── %s\n", raiz->str);

    printBonito(raiz->esq, nivel + 1);
}

/**
 * @brief Retorna a altura de um nó.
 *
 * @param no Ponteiro para o nó.
 * @return Altura do nó ou 0 se o nó for NULL.
 */
int altura(No *no)
{
    if (no == NULL)
        return 0;
    else
        return no->altura;
}

/**
 * @brief Retorna o maior entre dois inteiros.
 *
 * @param a Primeiro valor.
 * @param b Segundo valor.
 * @return O maior valor entre a e b.
 */
int max(int a, int b)
{
    return (a > b) ? a : b;
}
