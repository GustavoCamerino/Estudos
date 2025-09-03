#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct no_bst {
    char *palavra;
    struct no_bst *esq, *dir;
} NoBST;

typedef struct {
    NoBST *raiz;
} BST;

void inicializar_bst(BST *arvore);
void inserir_bst(BST *arvore, const char *palavra);
NoBST *buscar_bst(BST *arvore, const char *palavra);
int altura_bst(NoBST *no);
void liberar_bst(NoBST *no);

#endif