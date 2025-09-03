#include <iostream>
using namespace std;

// Prototipos
int potencia(int x, int y);

int main(int argc, char const *argv[])
{
    int a{0}, b{0};
    cout << "Insira os números: ";
    cin >> a >> b;
    int result = potencia(a, b);

    cout << a << " ^ " << b << " = " << result << endl;

    return 0;
}

int potencia(int x, int y)
{
    int result{1};
    for (int i = 0; i < y; i++)
    {
        result *= x;
    }
    return result;
}