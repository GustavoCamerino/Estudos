#include <iostream>
#include <vector>
#include <algorithm>

double calcMedia(std::vector<double> vetor);
double calcModa(std::vector<double> vetor);

int main(int argc, char const *argv[])
{
    std::vector<double> vetor = {3, 62, 6, 83, 4, 3};

    std::cout << "Média Calculada: " << calcMedia(vetor) << std::endl;
    std::cout << "Moda Calculada: " << calcModa(vetor) << std::endl;
    return 0;
}

double calcMedia(std::vector<double> vetor)
{
    int tamanho = vetor.size();
    double soma{0};
    for (double i : vetor)
    {
        soma += i;
    }
    if (tamanho != 0)
        return (double)soma / tamanho;
    else
    {
        return -1;
    }
}

double calcModa(std::vector<double> vetor)
{
    std::sort(vetor.begin(), vetor.end());
    int tamanho = vetor.size();

    double moda = vetor[0];
    int maxfreq = 0;

    for (int i = 0; i < tamanho; i++)
    {
        int freq = 0;
        for (int j = 0; j < tamanho; j++)
        {
            if (vetor[i] == vetor[j])
            {
                freq++;
            }
        }
        if (freq > maxfreq)
        {
            maxfreq = freq;
            moda = vetor[i];
        }
    }
    return moda;
}