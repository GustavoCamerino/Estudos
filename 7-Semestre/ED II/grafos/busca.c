#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define maxV 1024
#define BRANCO 0
#define CINZA 1
#define PRETO 2
typedef int bool;
typedef int TIPO_PESO;

static int dist[maxV], cor[maxV], pred[maxV];

int *fila;
int inicio, fim;

typedef struct Adjacencia
{
    int vertice;
    TIPO_PESO peso;
    struct Adjacencia *prox;
} T_Adjacencia;

typedef struct Vertice
{
    T_Adjacencia *cab;
} T_Vertice;

typedef struct Grafo
{
    int vertices;
    int arestas;
    T_Vertice *adj;
} T_Grafo;

// Prototipos
T_Grafo *Cria_Grafo(int v);
T_Adjacencia *Criar_Adjacencia(int v, int peso);
bool Cria_Aresta(T_Grafo *g, int vi, int vf, TIPO_PESO p);
void imprime(T_Grafo *g);

int main(int argc, char const *argv[])
{
    T_Grafo *g = Cria_Grafo(5);

    Cria_Aresta(g, 0, 1, 2);

    return 0;
}

void Inicializa_Fila(int maxN)
{
    fila = (int *)malloc(maxN * sizeof(int));
    inicio = 0;
    fim = 0;
}

int Fila_Vazia()
{
    return inicio == fim;
}

void Put_Fila(int item)
{
    fila[fim++] = item;
}

int Get_Fila()
{
    return fila[inicio++];
}

T_Grafo *Cria_Grafo(int v)
{
    T_Grafo *g = (T_Grafo *)malloc(sizeof(T_Grafo));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (T_Vertice *)malloc(v * sizeof(T_Vertice));

    for (int i = 0; i < v; i++)
    {
        g->adj[i].cab = NULL;
    }
    return g;
}

T_Adjacencia *Criar_Adjacencia(int v, int peso)
{
    T_Adjacencia *temp = (T_Adjacencia *)malloc(sizeof(T_Adjacencia));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

bool Cria_Aresta(T_Grafo *g, int vi, int vf, TIPO_PESO p)
{
    if (!g)
    {
        return (false);
    }
    if ((vf < 0) || (vf >= g->vertices))
    {
        return (false);
    }
    if ((vi < 0) || (vi >= g->vertices))
    {
        return (false);
    }
    T_Adjacencia *novo = Criar_Adjacencia(vf, p);

    novo->prox = g->adj[vi].cab;
    g->adj[vi].cab = novo;

    T_Adjacencia *novo2 = Criar_Adjacencia(vi, p);
    novo2->prox = g->adj[vf].cab;
    g->adj[vf].cab = novo2;

    g->arestas++;

    return true;
}

void imprime(T_Grafo *g)
{
    printf("Vertices %d. Arestas: %d \n", g->vertices, g->arestas);

    for (int i = 0; i < g->vertices; i++)
    {
        printf("v %d", i);
        T_Adjacencia *ad = g->adj[i].cab;
        while (ad)
        {
            printf(" adj[%d,%d]", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}