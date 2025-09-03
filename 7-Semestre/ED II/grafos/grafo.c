/**
 * @file grafo.c
 * @author Gustavo Camerino
 * @brief Algoritmo de um grafo generico
 * @version 0.1
 * @date 2025-08-30
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Vizinho
{
    int id_vizinho;
    struct Vizinho *prox;
} T_Vizinho;

typedef struct grafo
{
    int id_vertice;
    T_Vizinho *prim_vizinho;
    struct grafo *prox;
} T_Grafo;

// #--# Prototipos #--#
T_Grafo *inicializa();
void imprime_grafo(T_Grafo *g);
void libera_grafo(T_Grafo *g);
void libera_vizinho(T_Vizinho *v);
T_Grafo *busca_vertice(T_Grafo *g, int x);
T_Grafo *busca_aresta(T_Grafo *g, int v1, int v2);
T_Grafo *insere_vertice(T_Grafo *g, int x);
void insere_um_sentido(T_Grafo *g, int v1, int v2);
void insere_aresta(T_Grafo *g, int v1, int v2);
void insere_aresta_digrafo(T_Grafo *g, int v1, int v2);
void retira_um_sentido(T_Grafo *g, int v1, int v2);

// #--# Função Main() #--#

int main(int argc, char const *argv[])
{

    return 0;
}

// #--# Função que seta tudo do grafo como nulo #--#
T_Grafo *inicializa()
{
    return NULL;
}

// #--# Implementação das funções #--#

void imprime_grafo(T_Grafo *g)
{
    while (g != NULL)
    {
        printf("Vértice: %d\n", g->id_vertice);
        printf("Vizinhos: ");
        T_Vizinho *v = g->prim_vizinho;
        while (v != NULL)
        {
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}

void libera_grafo(T_Grafo *g)
{
    while (g != NULL)
    {
        libera_vizinho(g->prim_vizinho);
        T_Grafo *temp = g;
        g = g->prox;
        free(temp);
    }
}
void libera_vizinho(T_Vizinho *v)
{
    while (v != NULL)
    {
        T_Vizinho *temp = v;
        v = v->prox;
        free(temp);
    }
}

T_Grafo *busca_vertice(T_Grafo *g, int x)
{
    while ((g != NULL) && (g->id_vertice != x))
    {
        g = g->prox;
    }
    return g;
}

T_Grafo *busca_aresta(T_Grafo *g, int v1, int v2)
{
    T_Grafo *pv1 = busca_vertice(g, v1);
    T_Grafo *pv2 = busca_vertice(g, v2);
    T_Vizinho *resp = NULL;

    // #--# Checando se os vértices são nulos #--#
    if ((pv1 != NULL) && (pv2 != NULL))
    {
        // #--# Percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_vizinho;
        while ((resp != NULL) && (resp->id_vizinho != v2))
        {
            resp = resp->prox;
        }
    }
    return resp;
}

T_Grafo *insere_vertice(T_Grafo *g, int x)
{
    T_Grafo *p = busca_vertice(g, x);
    if (p == NULL)
    {
        p = (T_Grafo *)malloc(sizeof(T_Grafo));
        p->id_vertice = x;
        p->prox = g;
        p->prim_vizinho = NULL;
        g = p;
    }
    return g;
}

void insere_um_sentido(T_Grafo *g, int v1, int v2)
{
    T_Grafo *p = busca_vertice(g, v1);
    T_Vizinho *nova = (T_Vizinho *)malloc(sizeof(T_Vizinho));
    nova->id_vizinho = v2;
    nova->prox = p->prim_vizinho;
    p->prim_vizinho = nova;
}
void insere_aresta(T_Grafo *g, int v1, int v2)
{
    T_Vizinho *v = busca_aresta(g, v1, v2);
    if (v == NULL)
        insere_um_sentido(g, v1, v2);
    insere_um_sentido(g, v2, v1);
}

void insere_aresta_digrafo(T_Grafo *g, int v1, int v2)
{
    T_Vizinho *v = busca_aresta(g, v1, v2);
    if (v == NULL)
    {
        insere_um_sentido(g, v1, v2);
    }
}

void retira_um_sentido(T_Grafo *g, int v1, int v2)
{
    T_Grafo *p = busca_vertice(g, v1);
    if (p != NULL)
    {
        T_Vizinho *ant = NULL;
        T_Vizinho *atual = p->prim_vizinho;
        while ((atual) && (atual->id_vizinho != v2))
        {
            ant = atual;
            atual = atual->prox;
        }
        if (ant == NULL) // v2 era o primeiro nó da lista
            p->prim_vizinho = atual->prox;
        else
            ant->prox = atual->prox;
        free(atual);
    }
}