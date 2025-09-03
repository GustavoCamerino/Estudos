#include <iostream>
using namespace std;

double somaSerie(int N)
{
    double S = 1.0, fat = 1.0; // 0! = 1
    for (int i = 1; i <= N; i++)
    {
        fat *= i;       // fatorial acumulado
        S += 1.0 / fat; // soma o termo
    }
    return S;
}

int main()
{
    int N;
    cin >> N;
    cout << somaSerie(N) << endl;
}
