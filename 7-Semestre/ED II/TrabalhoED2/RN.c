#include "RN.h"

NoRN *criar_no_rn(const char *palavra, NoRN *nulo) {
    NoRN *novo = (NoRN *)malloc(sizeof(NoRN));
    if (novo) {
        novo->palavra = strdup(palavra);
        novo->cor = VERMELHO;
        novo->esq = novo->dir = novo->pai = nulo;
    }
    return novo;
}

void inicializar_rn(RN *arvore) {
    arvore->nulo = (NoRN *)malloc(sizeof(NoRN));
    arvore->nulo->cor = PRETO;
    arvore->nulo->esq = arvore->nulo->dir = arvore->nulo->pai = arvore->nulo;
    arvore->raiz = arvore->nulo;
    arvore->rotacoes = 0;
}

void rotacionar_esquerda_rn(RN *arvore, NoRN *x) {
    NoRN *y = x->dir;
    x->dir = y->esq;
    
    if (y->esq != arvore->nulo) {
        y->esq->pai = x;
    }
    
    y->pai = x->pai;
    
    if (x->pai == arvore->nulo) {
        arvore->raiz = y;
    } else if (x == x->pai->esq) {
        x->pai->esq = y;
    } else {
        x->pai->dir = y;
    }
    
    y->esq = x;
    x->pai = y;
    
    arvore->rotacoes++;
}

void rotacionar_direita_rn(RN *arvore, NoRN *y) {
    NoRN *x = y->esq;
    y->esq = x->dir;
    
    if (x->dir != arvore->nulo) {
        x->dir->pai = y;
    }
    
    x->pai = y->pai;
    
    if (y->pai == arvore->nulo) {
        arvore->raiz = x;
    } else if (y == y->pai->dir) {
        y->pai->dir = x;
    } else {
        y->pai->esq = x;
    }
    
    x->dir = y;
    y->pai = x;
    
    arvore->rotacoes++;
}

void ajustar_insercao_rn(RN *arvore, NoRN *z) {
    while (z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            NoRN *y = z->pai->pai->dir;
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacionar_esquerda_rn(arvore, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_direita_rn(arvore, z->pai->pai);
            }
        } else {
            NoRN *y = z->pai->pai->esq;
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacionar_direita_rn(arvore, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_esquerda_rn(arvore, z->pai->pai);
            }
        }
    }
    arvore->raiz->cor = PRETO;
}

void inserir_rn(RN *arvore, const char *palavra) {
    NoRN *z = criar_no_rn(palavra, arvore->nulo);
    NoRN *y = arvore->nulo;
    NoRN *x = arvore->raiz;
    
    while (x != arvore->nulo) {
        y = x;
        int cmp = strcmp(palavra, x->palavra);
        if (cmp < 0) {
            x = x->esq;
        } else if (cmp > 0) {
            x = x->dir;
        } else {
            free(z->palavra);
            free(z);
            return; // Palavra já existe
        }
    }
    
    z->pai = y;
    if (y == arvore->nulo) {
        arvore->raiz = z;
    } else if (strcmp(palavra, y->palavra) < 0) {
        y->esq = z;
    } else {
        y->dir = z;
    }
    
    z->esq = z->dir = arvore->nulo;
    z->cor = VERMELHO;
    
    ajustar_insercao_rn(arvore, z);
}

NoRN *buscar_rn(RN *arvore, const char *palavra) {
    NoRN *atual = arvore->raiz;
    while (atual != arvore->nulo) {
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

int altura_rn(NoRN *no, NoRN *nulo) {
    if (no == nulo) return -1;
    int altura_esq = altura_rn(no->esq, nulo);
    int altura_dir = altura_rn(no->dir, nulo);
    return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

void liberar_rn(NoRN *no, NoRN *nulo) {
    if (no != nulo) {
        liberar_rn(no->esq, nulo);
        liberar_rn(no->dir, nulo);
        free(no->palavra);
        free(no);
    }
}