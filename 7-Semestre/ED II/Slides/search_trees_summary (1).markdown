# 🌳 Estruturas de Árvores de Busca

**ABB • AVL • Rubro-Negra • Splay**

## 🔷 1. Árvore de Busca Binária (ABB / BST)

### 📌 Definição

Uma árvore onde:

- Cada nó contém uma **chave única**.
- A subárvore esquerda contém valores **menores** que o nó.
- A subárvore direita contém valores **maiores** que o nó.

### ✅ Vantagens

- Simples de implementar.
- Bom desempenho quando equilibrada.

### ❌ Desvantagens

- Pode **desbalancear facilmente**, degradando a eficiência.

### 🧠 Complexidades (média / pior caso)

| Operação | Média    | Pior Caso |
| :------- | :------- | :-------- |
| Busca    | O(log n) | O(n)      |
| Inserção | O(log n) | O(n)      |
| Remoção  | O(log n) | O(n)      |

### 💻 Exemplo de Código (Estrutura e Inserção)

```c
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da ABB
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na ABB
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

// Função para buscar um nó na ABB
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key > root->key) {
        return search(root->right, key);
    }
    return search(root->left, key);
}

// Função para imprimir a ABB em ordem
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}
```

## 🔶 2. Árvore AVL

### 📌 Definição

Primeira árvore de busca **autobalanceada**. Após inserções e remoções, a árvore aplica rotações para manter o equilíbrio.

### 🧮 Fator de Balanceamento (FB)

$FB = altura(dir) - altura(esq)$

A árvore é AVL se: $-1 \le FB \le 1$

### 🔄 Tipos de Rotações

- Rotação simples à esquerda/direita.
- Rotação dupla à esquerda/direita.

### ✅ Vantagens

- Altura sempre $O(\log n)$.
- Mantém desempenho previsível.

### ❌ Desvantagens

- Mais complexa para implementar.
- Rebalanceamento constante pode ser custoso.

### 📊 Complexidade

| Operação | Complexidade |
| :------- | :----------- |
| Busca    | O(log n)     |
| Inserção | O(log n)     |
| Remoção  | O(log n)     |

### 💻 Exemplo de Código (Estrutura e Cálculo de Altura/FB)

```c
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da AVL
typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Função para obter a altura de um nó
int height(AVLNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para obter o máximo de dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó AVL
AVLNode* newAVLNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    if (node == NULL) {
        perror("Failed to allocate memory for new AVL node");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(AVLNode *N) {
    if (N == NULL)
        return 0;
    return height(N->right) - height(N->left);
}
```

## 🔴⚫ 3. Árvore Rubro-Negra (Red-Black Tree)

### 📌 Definição

Árvore binária balanceada onde cada nó possui uma cor: **vermelho** ou **preto**, obedecendo as seguintes regras:

1. Todo nó é vermelho ou preto.
2. A raiz é sempre preta.
3. Nós vermelhos não têm filhos vermelhos.
4. Todo caminho da raiz até as folhas nulas contém o **mesmo número de nós pretos**.

### ✅ Vantagens

- Balanceamento menos rigoroso que AVL $\rightarrow$ menos rotações.
- Mais eficiente em operações de inserção/remoção em massa.

### ❌ Desvantagens

- Lógica de inserção/remoção mais complexa.
- Árvores podem ser mais altas que AVL.

### 📊 Complexidade

| Operação | Complexidade |
| :------- | :----------- |
| Busca    | O(log n)     |
| Inserção | O(log n)     |
| Remoção  | O(log n)     |

### 💻 Exemplo de Código (Estrutura de Nó)

```c
#include <stdio.h>
#include <stdlib.h>

// Definição de cores para os nós
typedef enum Color { RED, BLACK } Color;

// Definição da estrutura do nó da Árvore Rubro-Negra
typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
} RBNode;

// Ponteiro para o nó NULO (sentinela)
RBNode *NIL_NODE;

// Função para criar um novo nó Rubro-Negro
RBNode* createRBNode(int key, Color color, RBNode *parent, RBNode *nil) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new RBNode");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->color = color;
    newNode->parent = parent;
    newNode->left = nil;
    newNode->right = nil;
    return newNode;
}
```

## ⚡ 4. Árvore Splay

### 📌 Definição

Árvore **autoajustável** que move o nó acessado para a raiz por meio de rotações. Ideal para acessos repetidos ou dados com frequência de uso desigual.

### 🔁 Operações

Após qualquer operação (busca, inserção, remoção), o nó acessado é "**splayado**" para o topo.

### 🔄 Tipos de Rotações

- **Zig**: pai do nó é a raiz.
- **Zig-Zig**: duas rotações na mesma direção.
- **Zig-Zag**: rotações opostas.

### ✅ Vantagens

- Acesso frequente a um mesmo dado torna-o mais rápido com o tempo.
- Boa escolha para acessos com padrão repetitivo.

### ❌ Desvantagens

- Pode ficar desbalanceada temporariamente.
- Pior caso: O(n), embora raramente ocorra.

### 📊 Complexidade (amortizada)

| Operação | Complexidade |
| :------- | :----------- |
| Busca    | O(log n)* |
| Inserção | O(log n)* |
| Remoção  | O(log n)* |

*$Amortizado$

### 💻 Exemplo de Código (Estrutura de Nó e Operação Splay)

```c
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da Splay Tree
typedef struct SplayNode {
    int key;
    struct SplayNode *left;
    struct SplayNode *right;
} SplayNode;

// Função para criar um novo nó da Splay Tree
SplayNode* newSplayNode(int key) {
    SplayNode* node = (SplayNode*)malloc(sizeof(SplayNode));
    if (node == NULL) {
        perror("Failed to allocate memory for new Splay node");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função de rotação à direita
SplayNode* rightRotateSplay(SplayNode *x) {
    SplayNode *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Função de rotação à esquerda
SplayNode* leftRotateSplay(SplayNode *x) {
    SplayNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Função splay
SplayNode* splay(SplayNode *root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key) {
        if (root->left == NULL)
            return root;
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotateSplay(root);
        } else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotateSplay(root->left);
        }
        return (root->left == NULL) ? root : rightRotateSplay(root);
    } else {
        if (root->right == NULL)
            return root;
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotateSplay(root->right);
        } else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotateSplay(root);
        }
        return (root->right == NULL) ? root : leftRotateSplay(root);
    }
}

// Função de busca
SplayNode* searchSplay(SplayNode *root, int key) {
    return splay(root, key);
}
```

## 🔚 Conclusão: Comparação Geral

| Estrutura       | Busca               | Inserção            | Remoção             | Balanceamento | Ideal para...                     |
| :-------------- | :------------------ | :------------------ | :------------------ | :------------ | :-------------------------------- |
| **ABB**         | O(log n) / O(n)     | O(log n) / O(n)     | O(log n) / O(n)     | ❌            | Estruturas simples e pequenas     |
| **AVL**         | O(log n)            | O(log n)            | O(log n)            | ✅ Forte      | Busca frequente                   |
| **Rubro-Negra** | O(log n)            | O(log n)            | O(log n)            | ✅ Moderado   | Grandes inserções/remoções       |
| **Splay**       | O(log n)*           | O(log n)*           | O(log n)*           | ✅ Dinâmico   | Acessos repetidos, cachês de dados |

*$Amortizado$