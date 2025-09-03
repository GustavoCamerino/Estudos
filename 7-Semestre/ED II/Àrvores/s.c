#include <stdio.h>
#include <stdlib.h> // Necessário para malloc e free

// Definição da estrutura do nó da árvore
typedef struct sNoA
{
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

// --- Funções Auxiliares de Rotação ---

// Rotação para a Direita (Zig - quando o nó é filho esquerdo)
// Esta função realiza uma rotação simples para a direita em torno do 'no'.
// Retorna a nova raiz da subárvore após a rotação.
TNoA *rotacaoDireita(TNoA *no)
{
    TNoA *novaRaiz = no->esq; // O filho esquerdo se torna a nova raiz
    no->esq = novaRaiz->dir;  // O filho direito da nova raiz se torna o filho esquerdo do 'no'
    novaRaiz->dir = no;       // O 'no' original se torna o filho direito da nova raiz
    return novaRaiz;          // Retorna a nova raiz
}

// Rotação para a Esquerda (Zag - quando o nó é filho direito)
// Esta função realiza uma rotação simples para a esquerda em torno do 'no'.
// Retorna a nova raiz da subárvore após a rotação.
TNoA *rotacaoEsquerda(TNoA *no)
{
    TNoA *novaRaiz = no->dir; // O filho direito se torna a nova raiz
    no->dir = novaRaiz->esq;  // O filho esquerdo da nova raiz se torna o filho direito do 'no'
    novaRaiz->esq = no;       // O 'no' original se torna o filho esquerdo da nova raiz
    return novaRaiz;          // Retorna a nova raiz
}

// --- Função de Splay (Move o nó para a raiz) ---
// Esta função é o coração da Árvore Splay.
// Ela recebe a raiz da subárvore e a chave que queremos splayar (trazer para a raiz).
// Retorna a nova raiz da subárvore após o splay.
TNoA *splay(TNoA *raiz, int chave)
{
    // Caso base: se a árvore é nula ou a chave é a raiz
    // Se a raiz é nula, não há nada para splayar. Se a chave já é a raiz, não precisa splayar.
    if (raiz == NULL || raiz->chave == chave)
    {
        return raiz;
    }

    // Se a chave está na subárvore esquerda
    if (raiz->chave > chave)
    {
        // Se a chave não está na subárvore esquerda, não há nada para splayar
        // Isso significa que a chave não está na árvore ou está no 'raiz' (já tratado acima).
        if (raiz->esq == NULL)
        {
            return raiz;
        }

        // Tic-Tic (Zig-Zig): chave na subárvore esquerda do filho esquerdo
        // A chave está à esquerda do filho esquerdo. Realiza splay recursivamente e depois duas rotações para a direita.
        if (raiz->esq->chave > chave)
        {
            raiz->esq->esq = splay(raiz->esq->esq, chave); // Splay recursivo no filho do filho
            raiz = rotacaoDireita(raiz);                   // Primeira rotação
        }
        // Tic-Tac (Zig-Zag): chave na subárvore direita do filho esquerdo
        // A chave está à direita do filho esquerdo. Realiza splay recursivamente, uma rotação para a esquerda e uma para a direita.
        else if (raiz->esq->chave < chave)
        {
            raiz->esq->dir = splay(raiz->esq->dir, chave); // Splay recursivo no filho do filho
            if (raiz->esq->dir != NULL)                    // Se a subárvore direita do filho esquerdo não é nula
            {
                raiz->esq = rotacaoEsquerda(raiz->esq); // Primeira rotação
            }
        }

        // Rotação Zig final (se o filho esquerdo existe)
        // Se o filho esquerdo ainda existe (após as operações acima), significa que a chave ainda não está na raiz.
        // Realiza uma rotação final para a direita para trazer a chave para a raiz.
        return (raiz->esq == NULL) ? raiz : rotacaoDireita(raiz);
    }
    // Se a chave está na subárvore direita
    else
    {
        // Se a chave não está na subárvore direita, não há nada para splayar
        // Isso significa que a chave não está na árvore ou está no 'raiz' (já tratado acima).
        if (raiz->dir == NULL)
        {
            return raiz;
        }

        // Tac-Tac (Zag-Zag): chave na subárvore direita do filho direito
        // A chave está à direita do filho direito. Realiza splay recursivamente e depois duas rotações para a esquerda.
        if (raiz->dir->chave < chave)
        {
            raiz->dir->dir = splay(raiz->dir->dir, chave); // Splay recursivo no filho do filho
            raiz = rotacaoEsquerda(raiz);                  // Primeira rotação
        }
        // Tac-Tic (Zag-Zig): chave na subárvore esquerda do filho direito
        // A chave está à esquerda do filho direito. Realiza splay recursivamente, uma rotação para a direita e uma para a esquerda.
        else if (raiz->dir->chave > chave)
        {
            raiz->dir->esq = splay(raiz->dir->esq, chave); // Splay recursivo no filho do filho
            if (raiz->dir->esq != NULL)                    // Se a subárvore esquerda do filho direito não é nula
            {
                raiz->dir = rotacaoDireita(raiz->dir); // Primeira rotação
            }
        }

        // Rotação Zag final (se o filho direito existe)
        // Se o filho direito ainda existe (após as operações acima), significa que a chave ainda não está na raiz.
        // Realiza uma rotação final para a esquerda para trazer a chave para a raiz.
        return (raiz->dir == NULL) ? raiz : rotacaoEsquerda(raiz);
    }
}

// --- Funções da Árvore Splay ---

// Cria uma nova árvore vazia
TNoA *cria(void)
{
    return NULL; // Uma árvore vazia é representada por um ponteiro NULL
}

// Imprime a árvore (em ordem - inorder traversal)
// Esta função realiza um percurso em ordem na árvore, imprimindo os nós com identação
// para visualizar a estrutura da árvore.
void imprime(TNoA *nodo, int tab)
{
    if (nodo == NULL)
        return;

    // Imprime a subárvore direita primeiro (para visualização horizontal)
    imprime(nodo->dir, tab + 1); // CORREÇÃO: Alterado de 'printBonito' para 'imprime'

    // Imprime identação proporcional ao nível do nó
    for (int i = 0; i < tab; i++)
        printf("       "); // 7 espaços para alinhamento visual

    // Imprime o valor do nó com um símbolo de conexão
    printf("└── %d\n", nodo->chave);

    // Imprime a subárvore esquerda depois (para visualização horizontal)
    imprime(nodo->esq, tab + 1); // CORREÇÃO: Alterado de 'printBonito' para 'imprime'
}

// Função de Busca na Árvore Splay
// A busca na Árvore Splay é feita através da operação splay.
// O splay automaticamente move a chave buscada (se encontrada) para a raiz.
// Se a chave não for encontrada, o último nó acessado (o "vizinho" mais próximo)
// será movido para a raiz.
TNoA *busca(TNoA *no, int chave)
{
    return splay(no, chave);
}

// Função de Inserção na Árvore Splay
// Insere uma nova chave na árvore Splay. O nó inserido se torna a nova raiz.
TNoA *insere(TNoA *no, int chave)
{
    // Se a árvore está vazia, cria o primeiro nó
    if (no == NULL)
    {
        TNoA *novo = (TNoA *)malloc(sizeof(TNoA));
        if (novo == NULL)
        {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(EXIT_FAILURE); // Encerra o programa em caso de erro de alocação
        }
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    // Primeiro, fazemos um splay na árvore com a chave a ser inserida.
    // Isso trará o nó mais próximo da chave (ou o ponto de inserção) para a raiz.
    no = splay(no, chave);

    // Se a chave já existe, apenas retornamos a árvore (ela já está na raiz)
    if (no->chave == chave)
    {
        return no;
    }

    // Cria o novo nó
    TNoA *novo = (TNoA *)malloc(sizeof(TNoA));
    if (novo == NULL)
    {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(EXIT_FAILURE);
    }
    novo->chave = chave;

    // Se a chave a ser inserida é menor que a raiz atual
    if (chave < no->chave)
    {
        // O novo nó se torna a raiz
        // A antiga raiz se torna o filho direito do novo nó
        // A subárvore esquerda da antiga raiz se torna a subárvore esquerda do novo nó
        novo->dir = no;
        novo->esq = no->esq;
        no->esq = NULL; // A antiga raiz não tem mais filho esquerdo direto
    }
    // Se a chave a ser inserida é maior que a raiz atual
    else
    {
        // O novo nó se torna a raiz
        // A antiga raiz se torna o filho esquerdo do novo nó
        // A subárvore direita da antiga raiz se torna a subárvore direita do novo nó
        novo->esq = no;
        novo->dir = no->dir;
        no->dir = NULL; // A antiga raiz não tem mais filho direito direto
    }

    // O novo nó é a nova raiz da árvore
    return novo;
}

// Libera a memória alocada para a árvore (pós-ordem traversal)
// Esta função percorre a árvore em pós-ordem, liberando a memória de cada nó
// para evitar vazamentos de memória.
void libera(TNoA *no)
{
    if (no != NULL)
    {
        libera(no->esq); // Libera a subárvore esquerda
        libera(no->dir); // Libera a subárvore direita
        free(no);        // Libera o nó atual
    }
}

// --- Função Principal (Main) ---
int main(void)
{
    TNoA *raiz;
    raiz = cria(); // Inicializa a árvore como vazia

    int qt, value, x;

    // Lê a quantidade de elementos a serem inseridos
    printf("Digite a quantidade de elementos a serem inseridos: ");
    scanf("%i", &qt);

    // Insere os elementos na árvore
    printf("Digite os elementos a serem inseridos:\n");
    for (int i = 0; i < qt; i++)
    {
        scanf("%i", &value);
        raiz = insere(raiz, value); // Cada inserção move o nó inserido para a raiz
        printf("Arvore apos insercao de %d:\n", value);
        imprime(raiz, 0);
        printf("---\n");
    }

    // Lê a chave a ser buscada
    printf("Digite a chave a ser buscada: ");
    scanf("%i", &x);
    raiz = busca(raiz, x); // A busca move a chave encontrada para a raiz
    printf("Arvore apos busca por %d:\n", x);

    // Imprime a árvore final (com a última chave buscada/inserida na raiz)
    imprime(raiz, 0);
    printf("---\n");

    // Libera a memória da árvore antes de encerrar o programa
    libera(raiz);
    printf("Memoria da arvore liberada com sucesso.\n");

    return 0;
}