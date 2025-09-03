#include "AVL.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura_no_avl(NoAVL *no) {
    return (no == NULL) ? -1 : no->altura;
}

void atualizar_altura(NoAVL *no) {
    no->altura = max(altura_no_avl(no->esq), altura_no_avl(no->dir)) + 1;
}

NoAVL *criar_no_avl(const char *palavra) {
    NoAVL *novo = (NoAVL *)malloc(sizeof(NoAVL));
    if (novo) {
        novo->palavra = strdup(palavra);
        novo->altura = 0;
        novo->esq = novo->dir = NULL;
    }
    return novo;
}

NoAVL *rotacionar_direita(NoAVL *y, int *rotacoes) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;
    
    x->dir = y;
    y->esq = T2;
    
    atualizar_altura(y);
    atualizar_altura(x);
    
    (*rotacoes)++;
    return x;
}

NoAVL *rotacionar_esquerda(NoAVL *x, int *rotacoes) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;
    
    x->dir = T2;
    y->esq = x;
    
    atualizar_altura(x);
    atualizar_altura(y);
    
    (*rotacoes)++;
    return y;
}

int fator_balanceamento(NoAVL *no) {
    return (no == NULL) ? 0 : altura_no_avl(no->esq) - altura_no_avl(no->dir);
}

NoAVL *inserir_no_avl(NoAVL *no, const char *palavra, int *rotacoes) {
    if (no == NULL) return criar_no_avl(palavra);
    
    int cmp = strcmp(palavra, no->palavra);
    if (cmp < 0) {
        no->esq = inserir_no_avl(no->esq, palavra, rotacoes);
    } else if (cmp > 0) {
        no->dir = inserir_no_avl(no->dir, palavra, rotacoes);
    } else {
        return no; // Palavra já existe
    }
    
    atualizar_altura(no);
    int fb = fator_balanceamento(no);
    
    // Caso Esquerda-Esquerda
    if (fb > 1 && strcmp(palavra, no->esq->palavra) < 0) {
        return rotacionar_direita(no, rotacoes);
    }
    
    // Caso Direita-Direita
    if (fb < -1 && strcmp(palavra, no->dir->palavra) > 0) {
        return rotacionar_esquerda(no, rotacoes);
    }
    
    // Caso Esquerda-Direita
    if (fb > 1 && strcmp(palavra, no->esq->palavra) > 0) {
        no->esq = rotacionar_esquerda(no->esq, rotacoes);
        return rotacionar_direita(no, rotacoes);
    }
    
    // Caso Direita-Esquerda
    if (fb < -1 && strcmp(palavra, no->dir->palavra) < 0) {
        no->dir = rotacionar_direita(no->dir, rotacoes);
        return rotacionar_esquerda(no, rotacoes);
    }
    
    return no;
}

void inicializar_avl(AVL *arvore) {
    arvore->raiz = NULL;
    arvore->rotacoes = 0;
}

void inserir_avl(AVL *arvore, const char *palavra) {
    arvore->raiz = inserir_no_avl(arvore->raiz, palavra, &arvore->rotacoes);
}

NoAVL *buscar_avl(AVL *arvore, const char *palavra) {
    NoAVL *atual = arvore->raiz;
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

int altura_avl(NoAVL *no) {
    return altura_no_avl(no);
}

void liberar_avl(NoAVL *no) {
    if (no != NULL) {
        liberar_avl(no->esq);
        liberar_avl(no->dir);
        free(no->palavra);
        free(no);
    }
}