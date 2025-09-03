#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define maxV 1024
#define BRANCO 0
#define CINZA 1
#define PRETO 2

static int dist[maxV], cor[maxV], pred[maxV];

int *vetor;
int inicio, fim;

typedef int bool;
typedef int TIPO_PESO;

typedef struct adjacencia
{
    int vertice;
    TIPO_PESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

// ---------------- Criar grafo ----------------
GRAFO *criaGrafo(int v)
{
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));
    for (int i = 0; i < v; i++)
    {
        g->adj[i].cab = NULL;
    }
    return g;
}

// ---------------- Criar adjacência ----------------
ADJACENCIA *criaAdj(int v, int peso)
{
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

// ---------------- Criar aresta ----------------
bool criaAresta(GRAFO *gr, int vi, int vf, TIPO_PESO p)
{
    if (!gr)
        return false;
    if ((vf < 0) || (vf >= gr->vertices))
        return false;
    if ((vi < 0) || (vi >= gr->vertices))
        return false;

    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;

    ADJACENCIA *novo2 = criaAdj(vi, p);
    novo2->prox = gr->adj[vf].cab;
    gr->adj[vf].cab = novo2;

    gr->arestas++;
    return true;
}

// ---------------- Imprimir grafo ----------------
void imprime(GRAFO *gr)
{
    printf("Vertices: %d. Arestas: %d \n", gr->vertices, gr->arestas);

    for (int i = 0; i < gr->vertices; i++)
    {
        printf("v%d: ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad)
        {
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

// ---------------- Estrutura de fila ----------------
void init(int maxx)
{
    vetor = (int *)malloc(maxx * sizeof(int));
    inicio = fim = 0;
}

int empty()
{
    return inicio == fim;
}

void put(int item)
{
    vetor[fim++] = item;
}

int get()
{
    return vetor[inicio++];
}

// ---------------- BFS ----------------
void funcaox(GRAFO *gr, int raiz)
{
    int u;
    init(gr->vertices);

    for (int v = 0; v < gr->vertices; v++)
    {
        dist[v] = maxV;
        cor[v] = BRANCO;
        pred[v] = -1;
    }

    dist[raiz] = 0;
    cor[raiz] = CINZA;
    pred[raiz] = -1;
    put(raiz);

    while (!empty())
    {
        u = get();
        ADJACENCIA *v = gr->adj[u].cab;
        while (v)
        {
            if (cor[v->vertice] == BRANCO)
            {
                dist[v->vertice] = dist[u] + 1;
                pred[v->vertice] = u;
                cor[v->vertice] = CINZA;
                put(v->vertice);
            }
            v = v->prox;
        }
        cor[u] = PRETO;
    }
}

// ---------------- Imprimir predecessores ----------------
void imprime2(GRAFO *gr)
{
    for (int v = 0; v < gr->vertices; v++)
    {
        printf("%d, %d\n", pred[v], v);
    }
}

// ---------------- MAIN ----------------
int main()
{
    GRAFO *gr = criaGrafo(12);

    criaAresta(gr, 0, 1, 1);
    criaAresta(gr, 0, 2, 1);
    criaAresta(gr, 1, 3, 1);
    criaAresta(gr, 1, 6, 1);
    criaAresta(gr, 1, 7, 1);
    criaAresta(gr, 2, 3, 1);
    criaAresta(gr, 2, 4, 1);
    criaAresta(gr, 3, 4, 1);
    criaAresta(gr, 3, 8, 1);
    criaAresta(gr, 3, 9, 1);
    criaAresta(gr, 4, 9, 1);
    criaAresta(gr, 8, 9, 1);
    criaAresta(gr, 6, 7, 1);
    criaAresta(gr, 6, 10, 1);
    criaAresta(gr, 5, 11, 1);

    funcaox(gr, 0);

    imprime2(gr);

    return 0;
}
