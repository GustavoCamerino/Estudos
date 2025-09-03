#include <iostream>
#include <string>
#include <array> // <--- não se esqueça disso!

//  Prótotipo
template <typename T, unsigned long linhas, unsigned long colunas>
void printArray(const std::array<std::array<T, colunas>, linhas> &arr);

int main()
{
    std::array<std::string, 3> times{"Flamengo", "Corinthians", "Palmeiras"};

    // Exibir os times
    for (auto &index : times)
    {
        std::cout << index << std::endl;
    }

    // std::array<std::array<int, coluna>, linha> matriz
    std::array<std::array<int, 3>, 3> matriz{
        std::array{1, 2, 3},
        std::array{4, 5, 6},
        std::array{7, 8, 9}};

    for (int i = 0; i < matriz.size(); i++)
    {
        for (int j = 0; j < matriz.size(); j++)
        {
            std::cout << matriz[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}

template <typename T, unsigned long linhas, unsigned long colunas>
void printArray(const std::array<std::array<T, colunas>, linhas> &arr)
{
    for (const std::array<T, colunas> &linha : arr)
    {
        for (const T &valor : linha)
        {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
}