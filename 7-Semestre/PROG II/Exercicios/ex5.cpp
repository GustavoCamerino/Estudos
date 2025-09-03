#include <iostream>
#include <vector>
#include <cmath>
#include <string>

void BinarytoDecimal(int valor);

int main(int argc, char const *argv[])
{
    int numero{0};
    std::cout << "Digite um número para inserir no vetor: ";
    std::cin >> numero;

    BinarytoDecimal(numero);
    return 0;
}

void BinarytoDecimal(int valor)
{
    std::string s = std::to_string(valor);
    std::vector<int> v;
    for (auto c : s)
        v.push_back(c - '0');

    int n = v.size();
    int resultado{0};
    for (int i = 0; i < n; i++)
    {
        resultado += v[i] * std::pow(2, n - i - 1);
    }
    std::cout << "Decimal: " << resultado << std::endl;
}