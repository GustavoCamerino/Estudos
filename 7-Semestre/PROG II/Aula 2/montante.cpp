#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(int argc, char const *argv[])
{
    double C; // Capital Inicial
    double I; // Juros Mensal (Ex: 0.014 para 1,4%)
    int T;    // Quantidade de Meses

    cout << "Digite os valores do Capital Inicial {C}: ";
    cin >> C;

    cout << "Juros Mensais {I} (ex: 0.014 para 1,4%): ";
    cin >> I;

    cout << "Quantidade de Meses {T}: ";
    cin >> T;

    double M = 0;

    cout << fixed << setprecision(2);
    cout << "\nValor do montante com juros compostos a cada mês:\n";

    for (int i = 1; i <= T; i++)
    {
        M = C * pow(1 + I / 100, i);
        cout << "Mês " << i << ": R$ " << M << endl;
    }

    return 0;
}
