#include <stdio.h>
#include <stdlib.h>

typedef struct NoABB
{
    int info;
    struct NoABB *esq;
    struct NoABB *dir;
} NoABB;

NoABB *Busca(NoABB *No, int info)
{
    if (No == NULL)
        return NULL;
    else if (No->info == info)
    {
        return No;
    }
    else if (info > No->info)
    {
        return Busca(No->dir, info);
    }
    else
    {
        return Busca(No->esq, info);
    }
}

NoABB *CriaNo(int info)
{
    NoABB *NovoNo = malloc(sizeof(NoABB));
    if (NovoNo == NULL)
    {
        printf("Ocorreu um erro\n");
        exit(1);
    }
    NovoNo->info = info;
    NovoNo->esq = NULL;
    NovoNo->dir = NULL;
    return NovoNo;
}

NoABB *InsereNo(NoABB *raiz, int info)
{
    if (raiz == NULL)
    {
        NoABB *NovoNo = CriaNo(info);
        return NovoNo;
    }

    else if (info > raiz->info)
    {
        raiz->dir = InsereNo(raiz->dir, info);
    }
    else if (info < raiz->info)
    {
        raiz->esq = InsereNo(raiz->esq, info);
    }
    else
    {
        printf("Inserção inválida!\n"); // Chave já existente
        exit(1);
    }
    return raiz;
}

// Note that it is not a generic inorder successor
// function. It mainly works when the right child
// is not empty, which is  the case we need in
// BST delete.
NoABB *pegaSucessor(NoABB *atual)
{
    atual = atual->dir;
    while (atual != NULL && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

NoABB *ExcluiNo(NoABB *raiz, int info)
{
    if (raiz == NULL)
    {
        printf("Impossível excluir tal nó, pois ele não existe ou já foi excluído!\n");
        return NULL;
    }
    if (info < raiz->info)
    {
        raiz->esq = ExcluiNo(raiz->esq, info);
    }
    else if (info > raiz->info)
    {
        raiz->dir = ExcluiNo(raiz->dir, info);
    }
    else
    {
        // Caso 1 - Nó sem filhos
        if (raiz->dir == NULL && raiz->esq == NULL)
        {
            free(raiz);
            return NULL;
        }

        // Caso 2.1 - Nó só com um filho à esquerda
        if (raiz->dir == NULL && raiz->esq != NULL)
        {
            NoABB *aux = raiz->esq;
            free(raiz);
            return aux;
        }

        // Caso 2.1 - Nó só com um filho à direita
        else if (raiz->dir != NULL && raiz->esq == NULL)
        {
            NoABB *aux = raiz->dir;
            free(raiz);
            return aux;
        }
        // Caso 3 - Dois filhos
        else
        {
            NoABB *Sucessor = pegaSucessor(raiz);
            raiz->info = Sucessor->info;
            raiz->dir = ExcluiNo(raiz->dir, Sucessor->info);
        }
    }

    return raiz;
}