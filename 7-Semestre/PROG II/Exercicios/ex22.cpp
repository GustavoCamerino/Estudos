#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

float calcMedia(vector<int> vetor);

int main(int argc, char const *argv[])
{
    vector<int> vetor{1, 2, 3, 4};
    cout << "Média: " << calcMedia(vetor);
    return 0;
}

float calcMedia(vector<int> vetor)
{
    sort(vetor.begin(), vetor.end());

    int tamanho = vetor.size();
    int soma = 0;
    for (int i = 0; i < tamanho; i++)
    {
        soma += vetor.at(i);
    }

    return (double)soma / tamanho;
}