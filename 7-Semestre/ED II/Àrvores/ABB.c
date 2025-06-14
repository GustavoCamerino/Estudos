#include <stdio.h>
#include <stdlib.h>

typedef struct NoArv
{
    int valor;
    struct NoArv *esq;
    struct NoArv *dir;
} NoArv;

//    Prototipos
NoArv *insere(NoArv *raiz, int valor);
NoArv *criaNoArv(int valor);
void imprime(NoArv *raiz);

int main(int argc, char const *argv[])
{
    NoArv *raiz = NULL;
    raiz = insere(raiz, 50);
    imprime(raiz);

    printf("\2t Olá, seja bem vindo(a) ao menu de Àrvore Binária de Busca (ABB)\n");
    printf("Menu:\n");
    printf("---------------------");
    printf("|\t Digite");
    return 0;
}

NoArv *insere(NoArv *raiz, int valor)
{

    if (raiz == NULL)
    {
        NoArv *novoNo = criaNoArv(valor);
        return novoNo;
    }
    else
    {
        if (valor < raiz->valor)
        {
            raiz->esq = insere(raiz->esq, valor);
            printf("[Inserindo %d à esquerda...\n", valor);
        }
        else if (valor > raiz->valor)
        {
            raiz->dir = insere(raiz->dir, valor);
            printf("[Inserindo %d à direita...\n", valor);
        }
        return raiz;
    }
}

NoArv *criaNoArv(int valor)
{
    NoArv *novoNo = malloc(sizeof(NoArv));
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    novoNo->valor = valor;
    return novoNo;
}

void imprime(NoArv *raiz)
{
    if (raiz)
    {
        printf("%d \n", raiz->valor);
        imprime(raiz->esq);
        imprime(raiz->dir);
    }
}
