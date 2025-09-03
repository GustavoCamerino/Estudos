#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int x{10};
    int *ptr{nullptr};

    ptr = &x;

    cout << "Endereço de x = " << ptr << endl;

    // operador *: usado para derreferenciar (eliminar a direção) o ponteiro
    int valor = *ptr;

    cout << "Valor de prt: " << valor << endl;

    // trocando valor
    *ptr = 100;

    cout << "Valor de x agora: " << x << endl;
    return 0;
}
