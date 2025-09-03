#ifndef __AVL_H__
#define __AVL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct no_avl {
    char *palavra;
    int altura;
    struct no_avl *esq, *dir;
} NoAVL;

typedef struct {
    NoAVL *raiz;
    int rotacoes;
} AVL;

void inicializar_avl(AVL *arvore);
void inserir_avl(AVL *arvore, const char *palavra);
NoAVL *buscar_avl(AVL *arvore, const char *palavra);
int altura_avl(NoAVL *no);
void liberar_avl(NoAVL *no);

#endif