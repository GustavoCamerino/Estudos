#ifndef __RN_H__
#define __RN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { VERMELHO, PRETO } Cor;

typedef struct no_rn {
    char *palavra;
    Cor cor;
    struct no_rn *esq, *dir, *pai;
} NoRN;

typedef struct {
    NoRN *raiz;
    NoRN *nulo; // Nó sentinela
    int rotacoes;
} RN;

void inicializar_rn(RN *arvore);
void inserir_rn(RN *arvore, const char *palavra);
NoRN *buscar_rn(RN *arvore, const char *palavra);
int altura_rn(NoRN *no, NoRN *nulo);
void liberar_rn(NoRN *no, NoRN *nulo);

#endif