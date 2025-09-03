#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ehNumero(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]) && str[i] != '-')
        {
            return 0;
        }
    }
    return 1;
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

int main()
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
    return 0;
}
