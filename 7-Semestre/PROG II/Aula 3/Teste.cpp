#include <iostream>
#include <math.h>

//  Calcula o quadrado de um numero inteiro
int sqr(int a);
int maior(int a, int b, int c);

int main(int argc, char const *argv[])
{
    int a;
    std::cout << "Digite um número: ";
    std::cin >> a;
    std::cout << "O quadrado de " << a << " é: " << sqr(a) << " \n";

    std::cout << "Maior: " << maior(1, 2, 3) << std::endl;

    return 0;
}

int sqr(int a)
{
    return std::pow(a, 2);
}

int maior(int a, int b, int c)
{
    if (a > b && a > c)
    {
        return a;
    }
    else if (b > a && b > c)
    {
        return b;
    }

    return c;
}