#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BST.h"
#include "AVL.h"
#include "RN.h"

#define ARQUIVO_DADOS "Princeton.txt"
#define NUM_BUSCAS 100

void carregar_dados(const char *nome_arquivo, char ***dados, int *tamanho) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
    
    // Primeira passagem: contar o número de linhas
    *tamanho = 0;
    char linha[1024]; // Buffer maior para linhas longas
    while (fgets(linha, sizeof(linha), arquivo)) {
        (*tamanho)++;
    }
    
    // Alocar espaço para todos os ponteiros de uma vez
    *dados = malloc(*tamanho * sizeof(char *));
    if (!*dados) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    
    // Segunda passagem: ler e armazenar as linhas
    rewind(arquivo);
    for (int i = 0; i < *tamanho; i++) {
        if (!fgets(linha, sizeof(linha), arquivo)) {
            perror("Erro ao ler arquivo");
            exit(EXIT_FAILURE);
        }
        
        linha[strcspn(linha, "\n")] = '\0'; // Remove newline
        (*dados)[i] = strdup(linha);
        if (!(*dados)[i]) {
            perror("Erro ao duplicar string");
            exit(EXIT_FAILURE);
        }
    }
    
    fclose(arquivo);
}



void liberar_dados(char **dados, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(dados[i]);
    }
    free(dados);
}

void executar_testes(char **dados, int tamanho) {
    clock_t inicio, fim;
    
    // Teste BST
    BST bst;
    inicializar_bst(&bst);
    
    inicio = clock();
    for (int i = 0; i < tamanho; i++) {
        inserir_bst(&bst, dados[i]);
    }
    fim = clock();
    double tempo_insercao_bst = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    inicio = clock();
    for (int i = 0; i < NUM_BUSCAS; i++) {
        int indice = rand() % tamanho;
        buscar_bst(&bst, dados[indice]);
    }
    fim = clock();
    double tempo_busca_bst = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    int alturaBST = altura_bst(bst.raiz);
    
    // Teste AVL
    AVL avl;
    inicializar_avl(&avl);
    
    inicio = clock();
    for (int i = 0; i < tamanho; i++) {
        inserir_avl(&avl, dados[i]);
    }
    fim = clock();
    double tempo_insercao_avl = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    inicio = clock();
    for (int i = 0; i < NUM_BUSCAS; i++) {
        int indice = rand() % tamanho;
        buscar_avl(&avl, dados[indice]);
    }
    fim = clock();
    double tempo_busca_avl = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    int alturaAvl = altura_avl(avl.raiz);
    
    // Teste RN
    RN rn;
    inicializar_rn(&rn);
    
    inicio = clock();
    for (int i = 0; i < tamanho; i++) {
        inserir_rn(&rn, dados[i]);
    }
    fim = clock();
    double tempo_insercao_rn = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    inicio = clock();
    for (int i = 0; i < NUM_BUSCAS; i++) {
        int indice = rand() % tamanho;
        buscar_rn(&rn, dados[indice]);
    }
    fim = clock();
    double tempo_busca_rn = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    int alturaRN = altura_rn(rn.raiz, rn.nulo);
    
    // Exibir resultados
    printf("Resultados:\n");
    printf("-------------------------------------------------\n");
    printf("Estrutura | Inserção (s) | Busca (s) | Altura | Rotações\n");
    printf("-------------------------------------------------\n");
    printf("BST       | %-12.6f | %-9.6f | %-6d | N/A\n", tempo_insercao_bst, tempo_busca_bst, alturaBST);
    printf("AVL       | %-12.6f | %-9.6f | %-6d | %d\n", tempo_insercao_avl, tempo_busca_avl, alturaAvl, avl.rotacoes);
    printf("RN        | %-12.6f | %-9.6f | %-6d | %d\n", tempo_insercao_rn, tempo_busca_rn, alturaRN, rn.rotacoes);
    printf("-------------------------------------------------\n");
    
    // Liberar memória
    liberar_bst(bst.raiz);
    liberar_avl(avl.raiz);
    liberar_rn(rn.raiz, rn.nulo);
    free(rn.nulo);
}

int main() {
    srand(time(NULL));
    
    char **dados;
    int tamanho;
    
    carregar_dados(ARQUIVO_DADOS, &dados, &tamanho);
    executar_testes(dados, tamanho);
    liberar_dados(dados, tamanho);
    
    return 0;
}