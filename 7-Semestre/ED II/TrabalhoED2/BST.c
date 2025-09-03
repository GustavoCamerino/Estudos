#include "BST.h"

void inicializar_bst(BST *arvore) {
    arvore->raiz = NULL;
}

NoBST *criar_no_bst(const char *palavra) {
    NoBST *novo = (NoBST *)malloc(sizeof(NoBST));
    if (novo) {
        novo->palavra = strdup(palavra);
        novo->esq = novo->dir = NULL;
    }
    return novo;
}

void inserir_bst(BST *arvore, const char *palavra) {
    NoBST **atual = &arvore->raiz;
    
    while (*atual != NULL) {
        int cmp = strcmp(palavra, (*atual)->palavra);
        if (cmp < 0) {
            atual = &(*atual)->esq;
        } else if (cmp > 0) {
            atual = &(*atual)->dir;
        } else {
            return; // Palavra já existe
        }
    }
    *atual = criar_no_bst(palavra);
}

NoBST *buscar_bst(BST *arvore, const char *palavra) {
    NoBST *atual = arvore->raiz;
    while (atual != NULL) {
        int cmp = strcmp(palavra, atual->palavra);
        if (cmp < 0) {
            atual = atual->esq;
        } else if (cmp > 0) {
            atual = atual->dir;
        } else {
            return atual;
        }
    }
    return NULL;
}

int altura_bst(NoBST *no) {
    if (no == NULL) return -1;
    int altura_esq = altura_bst(no->esq);
    int altura_dir = altura_bst(no->dir);
    return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

void liberar_bst(NoBST *no) {
    if (no != NULL) {
        liberar_bst(no->esq);
        liberar_bst(no->dir);
        free(no->palavra);
        free(no);
    }
}