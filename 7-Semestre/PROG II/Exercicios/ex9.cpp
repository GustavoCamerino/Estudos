#include <iostream>
#include <vector>

std::vector<char> stringParaVetor(const std::string &texto);
std::string paraMaiusculo(const std::string &texto);

int main(int argc, char const *argv[])
{
    std::string nome;
    std::cout << "Digite um texto: ";
    std::getline(std::cin, nome);

    std::vector<char> vetor = stringParaVetor(nome);
    std::string convertido = paraMaiusculo(nome);

    std::cout << "Vetor de caracteres: ";
    for (char c : vetor)
    {
        std::cout << c << ' ';
    }
    std::cout << "\nTexto em maiúsculo: " << convertido << std::endl;

    return 0;
}

std::vector<char> stringParaVetor(const std::string &texto)
{
    std::vector<char> vetor(texto.begin(), texto.end());
    return vetor;
}

std::string paraMaiusculo(const std::string &texto)
{
    std::string palavra = texto;
    int TamanhoPalavra = palavra.size();

    for (int i{0}; i < TamanhoPalavra; i++)
    {
        if (palavra[i] >= 97 && palavra[i] <= 122)
        {
            palavra[i] -= 32;
        }
    }
    return palavra;
}
