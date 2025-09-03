#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10

void exibirMatriz(float matriz[MAX][MAX + 1], int n)
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

int main()
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
    exibirMatriz(matriz, n);

    gauss(matriz, resultado, n);

    printf("Solução:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %.3f\n", i + 1, resultado[i]);
    }

    return 0;
}
