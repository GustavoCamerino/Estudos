/**
 * @file AVL.c
 * @author Gustavo Camerino de Carvalho
 * @brief Implementação de Árvore AVL para armazenamento e busca de strings,
 *        com funções para criar nós, inserir elementos, buscar elementos,
 *        imprimir a árvore de forma visual, e manter o balanceamento
 *        automático através de rotações simples e duplas.
 *
 * @version 0.1
 * @date 2025-06-14
 *
 * @copyright Copyright (c) 2025
 *
 * @details
 * Este arquivo implementa uma Árvore AVL, uma árvore binária de busca
 * balanceada, que mantém a propriedade de altura balanceada entre
 * subárvores esquerda e direita para garantir busca, inserção e remoção
 * em tempo O(log n).
 *
 * As principais funcionalidades incluem:
 * - Criação de novos nós com strings
 * - Inserção de novos nós mantendo o balanceamento
 * - Busca de nós por string
 * - Impressão estruturada da árvore
 * - Funções auxiliares para cálculo de altura e fator de balanceamento
 * - Rotação simples à direita e esquerda para correção de balanceamento
 * - Rotação dupla (direita e esquerda) para casos especiais de desbalanceamento
 *
 * @note
 * Este código não implementa remoção de nós.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da árvore AVL
typedef struct NoAvl
{
    char str[255];     // String armazenada no nó (chave)
    struct NoAvl *esq; // Ponteiro para o filho esquerdo
    struct NoAvl *dir; // Ponteiro para o filho direito
    int altura;        // Altura do nó na árvore (para balanceamento)
} NoAvl;

// Protótipos das funções utilizadas
NoAvl *CriaNo(const char *str);
NoAvl *InsereNo(NoAvl *raiz, const char *str);
NoAvl *BuscaNo(NoAvl *raiz, const char *str);
NoAvl *rot_dir(NoAvl *P);
NoAvl *rot_esq(NoAvl *P);
NoAvl *rot_dupla_dir(NoAvl *P);
NoAvl *rot_dupla_esq(NoAvl *P);
int altura(NoAvl *no);
int FB(NoAvl *No);
int max(int a, int b);
void printBonito(NoAvl *raiz, int nivel);

// Função principal
int main()
{
    NoAvl *raiz = NULL; // Inicializa a raiz da árvore como vazia

    // Insere algumas strings na árvore AVL
    raiz = InsereNo(raiz, "manga");
    raiz = InsereNo(raiz, "abacaxi");
    raiz = InsereNo(raiz, "banana");
    raiz = InsereNo(raiz, "carambola");
    raiz = InsereNo(raiz, "laranja");
    raiz = InsereNo(raiz, "uva");

    // Imprime a árvore formatada
    printf("\n🌲 Árvore Binária:\n\n");
    printBonito(raiz, 0);

    return 0;
}

// Cria um novo nó com a string fornecida
NoAvl *CriaNo(const char *str)
{
    // Verifica se a string é válida
    if (str == NULL || strlen(str) == 0)
    {
        printf("[ERRO, IMPOSSÍVEL CRIAR NÓ POIS O ELEMENTO STRING É NULO/INVÁLIDO\n]");
        exit(1);
    }

    // Aloca memória para o novo nó
    NoAvl *novoNo = (NoAvl *)malloc(sizeof(NoAvl));
    if (novoNo == NULL)
    {
        printf("Erro de alocação de memória\n");
        exit(1);
    }

    // Copia a string para o nó e inicializa os filhos como NULL
    strcpy(novoNo->str, str);
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 1; // Novo nó sempre começa com altura 1 (folha)
    return novoNo;
}

// Busca um nó na árvore que contenha a string especificada
NoAvl *BuscaNo(NoAvl *raiz, const char *str)
{
    if (raiz == NULL) // Se a árvore estiver vazia, retorna NULL
    {
        return NULL;
    }

    // Compara a string do nó atual com a buscada
    int cmp = strcmp(str, raiz->str);

    if (cmp == 0) // Achou o nó que contém a string
        return raiz;

    if (cmp < 0) // Se a string buscada é menor, vai para a subárvore esquerda
        return BuscaNo(raiz->esq, str);
    else // Caso contrário, vai para a subárvore direita
        return BuscaNo(raiz->dir, str);
}

// Insere um novo nó com a string fornecida e mantém o balanceamento AVL
NoAvl *InsereNo(NoAvl *raiz, const char *str)
{
    // Caso base: se a árvore/subárvore está vazia, cria um novo nó
    if (raiz == NULL)
    {
        NoAvl *novoNo = CriaNo(str);
        printf("-- Inserindo %s na raiz como novo nó\n", str);
        return novoNo;
    }

    // Compara a string a ser inserida com a do nó atual para decidir o caminho
    int cmp = strcmp(str, raiz->str);

    if (cmp < 0) // Se for menor, insere na subárvore esquerda
    {
        raiz->esq = InsereNo(raiz->esq, str);
        printf("-- Inserindo %s à esquerda\n", str);
    }
    else if (cmp > 0) // Se for maior, insere na subárvore direita
    {
        raiz->dir = InsereNo(raiz->dir, str);
        printf("-- Inserindo %s à direita\n", str);
    }
    else // Se já existir o valor na árvore, não insere novamente
    {
        printf("-- Valor %s já existe na árvore\n", str);
    }

    // Atualiza a altura do nó atual após inserção
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    // Calcula o fator de balanceamento do nó atual
    int fb = FB(raiz);

    // Para decisões de rotação, compara a string com os filhos (se existirem)
    int cmpdir = raiz->dir ? strcmp(str, raiz->dir->str) : 0;
    int cmpesq = raiz->esq ? strcmp(str, raiz->esq->str) : 0;

    // Casos de desbalanceamento e suas correções:

    // Caso 1: Desbalanceamento à esquerda - rotação simples à direita
    if (fb > 1 && cmpesq < 0)
        return rot_dir(raiz);

    // Caso 2: Desbalanceamento à direita - rotação simples à esquerda
    if (fb < -1 && cmpdir > 0)
        return rot_esq(raiz);

    // Caso 3: Desbalanceamento à esquerda com filho direito - rotação dupla à direita
    if (fb > 1 && cmpesq > 0)
        return rot_dupla_dir(raiz);

    // Caso 4: Desbalanceamento à direita com filho esquerdo - rotação dupla à esquerda
    if (fb < -1 && cmpdir < 0)
        return rot_dupla_esq(raiz);

    // Retorna a raiz (possivelmente atualizada após rotações)
    return raiz;
}

// Função para imprimir a árvore de forma visual "bonita"
void printBonito(NoAvl *raiz, int nivel)
{
    if (raiz == NULL)
        return;

    // Imprime a subárvore direita primeiro (vai para cima na visualização)
    printBonito(raiz->dir, nivel + 1);

    // Imprime indentação proporcional ao nível do nó
    for (int i = 0; i < nivel; i++)
        printf("       "); // 7 espaços para alinhamento visual

    // Imprime o valor do nó com um símbolo de conexão
    printf("└── %s\n", raiz->str);

    // Imprime a subárvore esquerda depois (vai para baixo na visualização)
    printBonito(raiz->esq, nivel + 1);
}

// Rotação simples à direita para balancear a árvore
NoAvl *rot_dir(NoAvl *P)
{
    NoAvl *U = P->esq; // U é filho esquerdo de P
    P->esq = U->dir;   // A subárvore direita de U vira subárvore esquerda de P
    U->dir = P;        // P vira filho direito de U

    // Atualiza as alturas dos nós envolvidos na rotação
    P->altura = 1 + max(altura(P->esq), altura(P->dir));
    U->altura = 1 + max(altura(U->esq), altura(U->dir));

    return U; // Retorna o novo nó raiz da subárvore rotacionada
}

// Rotação simples à esquerda para balancear a árvore
NoAvl *rot_esq(NoAvl *P)
{
    NoAvl *Z = P->dir; // Z é filho direito de P
    P->dir = Z->esq;   // A subárvore esquerda de Z vira subárvore direita de P
    Z->esq = P;        // P vira filho esquerdo de Z

    // Atualiza as alturas dos nós envolvidos na rotação
    P->altura = 1 + max(altura(P->esq), altura(P->dir));
    Z->altura = 1 + max(altura(Z->esq), altura(Z->dir));

    return Z; // Retorna o novo nó raiz da subárvore rotacionada
}

// Rotação dupla à direita: primeiro esquerda no filho esquerdo, depois direita na raiz
NoAvl *rot_dupla_dir(NoAvl *P)
{
    P->esq = rot_esq(P->esq);
    return rot_dir(P);
}

// Rotação dupla à esquerda: primeiro direita no filho direito, depois esquerda na raiz
NoAvl *rot_dupla_esq(NoAvl *P)
{
    P->dir = rot_dir(P->dir);
    return rot_esq(P);
}

// Retorna a altura do nó (retorna -1 se nó for NULL, para convenção)
int altura(NoAvl *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

// Calcula o fator de balanceamento (FB) do nó
// FB = altura(esquerda) - altura(direita)
int FB(NoAvl *No)
{
    if (No == NULL)
        return 0;
    return altura(No->esq) - altura(No->dir);
}

// Retorna o máximo entre dois valores inteiros
int max(int a, int b)
{
    return (a > b) ? a : b;
}
