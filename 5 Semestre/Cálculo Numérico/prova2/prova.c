#include <stdio.h>
#include <math.h>

int main()
{
    float x = 2;
    float result_vector[11];

    // Primeiro loop: Calculando e armazenando os resultados
    for (int i = 0; i < 11; i++)
    {
        result_vector[i] = log(x) + 2.09 * x + 3.8;
        x += 0.1;
    }

    printf("\n");

    // Segundo loop: Exibindo os resultados e incrementando 'a'
    float a = 2.0; // Definir 'a' fora do loop para iniciar de 2 e incrementar
    for (int i = 0; i < 11; i++)
    {
        printf("%.1f ", a);               // Exibindo 'a' como float com uma casa decimal
        printf("%f\n", result_vector[i]); // Exibindo o resultado
        a += 0.1;                         // Incrementando 'a'
    }

    return 0;
}
