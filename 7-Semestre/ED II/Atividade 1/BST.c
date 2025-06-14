#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No
{
    char str[250];
    struct No *esq;
    struct No *dir;
} No;

//  Prototipos
No *CriaNo(const char *str);
No *InsereNo(No *raiz, const char *str);
No *BuscaNo(No *raiz, const char *str);
void printBonito(No *raiz, int nivel);

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

    strcpy(novoNo->str, str); // Copiando a string corretamente
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

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
        printf("-- Valor %s já existe na àrvore\n", str);
    }
    return raiz;
}

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

void printBonito(No *raiz, int nivel)
{
    if (raiz == NULL)
        return;

    // Primeiro, imprime a subárvore direita (vai para o topo visualmente)
    printBonito(raiz->dir, nivel + 1);

    // Indenta de acordo com o nível atual
    for (int i = 0; i < nivel; i++)
        printf("       "); // 7 espaços para alinhamento visual

    // Imprime o conteúdo do nó
    printf("└── %s\n", raiz->str);

    // Depois, imprime a subárvore esquerda (vai para baixo visualmente)
    printBonito(raiz->esq, nivel + 1);
}
