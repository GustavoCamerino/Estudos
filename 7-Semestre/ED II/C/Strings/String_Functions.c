#include <stdio.h>
#include <string.h>

int main()
{
    // STRLEN verifica o tamanho de cada Stringo
    char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Tem 26 letras
    char ola_mundo[] = "Ola Mundo";                 // Tem 8 letras
    char palavra[100];
    scanf("%99s", palavra); //  Insere palavra
    printf("%ld\n", strlen(alfabeto));
    printf("%ld\n", strlen(ola_mundo));
    printf("%s\n", palavra);
    return 0;
}