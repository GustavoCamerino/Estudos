#include <iostream>
#include <vector>
using namespace std;

// Prototipos
int maior(const vector<int> &vetor);

int main(int argc, char const *argv[])
{
    vector<int> vetor{1, 51, 6, 99, -1, -222222, 9};
    int numero = maior(vetor);
    cout << "Esse é o maior: " << numero << endl;

    return 0;
}

int maior(const vector<int> &vetor)
{
    if (vetor.empty())
        return -1;
    int numero{vetor.at(0)};
    for (int i : vetor)
    {
        if (i > numero)
            numero = i;
    }
    return numero;
}