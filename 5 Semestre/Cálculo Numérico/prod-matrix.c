#include <stdio.h>
#include <stdlib.h>

void lerMatriz(int matriz[][10], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void exibirMatriz(int matriz[][10], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
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
        return 1;
    }

    printf("Digite os elementos da matriz A:\n");
    lerMatriz(A, linhasA, colunasA);
    printf("Digite os elementos da matriz B:\n");
    lerMatriz(B, linhasB, colunasB);

    multiplicarMatrizes(A, B, C, linhasA, colunasA, colunasB);

    printf("Matriz A:\n");
    exibirMatriz(A, linhasA, colunasA);

    printf("Matriz B:\n");
    exibirMatriz(B, linhasB, colunasB);

    printf("Resultado da multiplicação (Matriz C):\n");
    exibirMatriz(C, linhasA, colunasB);

    return 0;
}
