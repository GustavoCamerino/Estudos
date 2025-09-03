#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 10

// Função para exibir matriz de inteiros
void exibirMatrizInt(int matriz[][10], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para exibir matriz de floats
void exibirMatrizFloat(float matriz[MAX][MAX + 1], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%8.3f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void gauss(float matriz[MAX][MAX + 1], float resultado[MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (fabs(matriz[i][i]) < 1e-6)
        {
            printf("Erro: pivô zero encontrado.\n");
            return;
        }

        for (int j = i + 1; j < n; j++)
        {
            float fator = matriz[j][i] / matriz[i][i];
            for (int k = i; k <= n; k++)
            {
                matriz[j][k] -= fator * matriz[i][k];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        resultado[i] = matriz[i][n];
        for (int j = i + 1; j < n; j++)
        {
            resultado[i] -= matriz[i][j] * resultado[j];
        }
        resultado[i] /= matriz[i][i];
    }
}

int calcularDeterminante(int matriz[][10], int n)
{
    if (n == 1)
    {
        return matriz[0][0];
    }
    else if (n == 2)
    {
        return (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
    }

    int det = 0, submatriz[10][10];
    for (int x = 0; x < n; x++)
    {
        int subi = 0;
        for (int i = 1; i < n; i++)
        {
            int subj = 0;
            for (int j = 0; j < n; j++)
            {
                if (j == x)
                    continue;
                submatriz[subi][subj] = matriz[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * matriz[0][x] * calcularDeterminante(submatriz, n - 1);
    }
    return det;
}

void lerMatriz(int matriz[][10], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j   = 0; j < colunas; j++)
        {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void multiplicarMatrizes(int A[][10], int B[][10], int C[][10], int linhasA, int colunasA, int colunasB)
{
    for (int i = 0; i < linhasA; i++)
    {
        for (int j = 0; j < colunasB; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < colunasA; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    printf("Seja Bem-vindo ao sistema geral de resolução de matrizes criada por Camerino\n");
    printf("Digite 1 para multiplicar matrizes\nDigite 2 para fazer o determinante\nDigite 3 para resolver as incógnitas\n");

    int flag;

    // Menu de opções
    while (1)
    {
        printf("\nEscolha uma opção (1-3): ");
        scanf("%d", &flag);

        if (flag == 1)
        {
            int linhasA, colunasA, linhasB, colunasB;
            int A[10][10], B[10][10], C[10][10];

            printf("Digite o número de linhas da matriz A: ");
            scanf("%d", &linhasA);
            printf("Digite o número de colunas da matriz A: ");
            scanf("%d", &colunasA);

            printf("Digite o número de linhas da matriz B: ");
            scanf("%d", &linhasB);
            printf("Digite o número de colunas da matriz B: ");
            scanf("%d", &colunasB);

            if (colunasA != linhasB)
            {
                printf("Erro: Número de colunas da matriz A deve ser igual ao número de linhas da matriz B.\n");
                continue;
            }

            printf("Digite os elementos da matriz A:\n");
            lerMatriz(A, linhasA, colunasA);
            printf("Digite os elementos da matriz B:\n");
            lerMatriz(B, linhasB, colunasB);

            multiplicarMatrizes(A, B, C, linhasA, colunasA, colunasB);

            printf("Matriz A:\n");
            exibirMatrizInt(A, linhasA, colunasA);

            printf("Matriz B:\n");
            exibirMatrizInt(B, linhasB, colunasB);

            printf("Resultado da multiplicação (Matriz C):\n");
            exibirMatrizInt(C, linhasA, colunasB);
        }
        else if (flag == 2)
        {
            int n;
            int matriz[10][10];

            printf("Digite a ordem da matriz quadrada: ");
            scanf("%d", &n);

            printf("Digite os elementos da matriz:\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    scanf("%d", &matriz[i][j]);
                }
            }

            printf("Determinante da Matriz: %d\n", calcularDeterminante(matriz, n));
        }
        else if (flag == 3)
        {
            int n;
            float matriz[MAX][MAX + 1], resultado[MAX];

            printf("Digite o número de variáveis: ");
            scanf("%d", &n);

            printf("Digite os coeficientes da matriz aumentada (incluindo os termos independentes):\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j <= n; j++)
                {
                    scanf("%f", &matriz[i][j]);
                }
            }

            printf("Matriz aumentada inicial:\n");
            exibirMatrizFloat(matriz, n);

            gauss(matriz, resultado, n);

            printf("Solução:\n");
            for (int i = 0; i < n; i++)
            {
                printf("x%d = %.3f\n", i + 1, resultado[i]);
            }
        }
        else
        {
            printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}
