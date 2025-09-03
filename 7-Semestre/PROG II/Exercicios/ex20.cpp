#include <iostream>
using namespace std;

template <typename T>
T max3(T valor1, T valor2, T valor3)
{
    T maxValor = valor1;
    if (valor2 > maxValor)
        maxValor = valor2;
    if (valor3 > maxValor)
        maxValor = valor3;
    return maxValor;
}

int main()
{
    int x;
    double y;
    char z;

    cout << "Digite um valor inteiro: ";
    cin >> x;
    cout << "Digite um valor double: ";
    cin >> y;
    cout << "Digite um valor char: ";
    cin >> z;

    double maior = max3<double>(x, y, z); // converte todos para double
    cout << "O maior de todos é: " << maior << endl;

    return 0;
}
