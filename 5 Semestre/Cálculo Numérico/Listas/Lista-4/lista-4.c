#include <stdio.h>
#include <math.h>
int main()
{
    double vector[9] = {1, 1.125, 1.250, 1.375, 1.500, 1.625, 1.750, 1.875, 2};
    int i = 0;
    int j = 0;
    int k = 0;
    double vector_results[9];
    for (i = 0; i < 9; i++)
    {
        vector_results[i] = sin(vector[i]) + vector[i];
    }
    printf("|");
    for (k = 0; k < 9; k++)
    {
        printf(" %.4f |", vector[k]);
    }
    printf("\n");
    printf("|");
    for (j = 0; j < 9; j++)
    {
        printf(" %.4f |", vector_results[j]);
    }
    return 0;
}