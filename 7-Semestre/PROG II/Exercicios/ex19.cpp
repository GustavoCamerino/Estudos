#include <iostream>
#include <cmath>
using namespace std;

double somaSerie(double x)
{
    double S = 1.0, fat = 1.0, termo = 1.0; // começa com 1 (x^0 / 0!)
    int i = 1;

    while (termo > 1e-6 || termo < -1e-6)
    {                              // enquanto |termo| > 10^-6
        fat *= i;                  // atualiza fatorial
        termo = (pow(x, i)) / fat; // termo atual
        S += termo;
        i++;
    }
    return S;
}

int main()
{
    double x;
    cout << "Digite x: ";
    cin >> x;
    cout << "e^" << x << " = " << somaSerie(x) << endl;
}
