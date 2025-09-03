#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

// Prototipos
int geraAleatorio(int a, int b);

int main(int argc, char const *argv[])
{
    srand(static_cast<unsigned int>(time(0)));

    const int TAMANHO_PISTA = 70;

    int posTartaruga = 1;
    int posLebre = 1;

    std::cout << "Corrida Maluca Começou!!!!" << std::endl;
    std::cout << "A pista possui " << TAMANHO_PISTA << " (m) de comprimento" << std::endl;

    while (posTartaruga < TAMANHO_PISTA && posLebre < TAMANHO_PISTA)
    {
        int movimentoTartaruga = geraAleatorio(1, 10);
        int movimentoLebre = geraAleatorio(1, 10);
        if (movimentoTartaruga >= 1 && movimentoTartaruga <= 5)
        {
            std::cout << "Sem base isso!!!\nA Tartaruga tá a 1000 km/h" << std::endl;
            posTartaruga += 5;
        }
        else if (movimentoTartaruga)
        {
            std::cout << "Opa, segura Peão!!" << std::endl;
            posTartaruga -= 2;
        }
        else
        {
            std::cout << "A Tartaruga tá andando lentamente" << std::endl;
            posTartaruga += 1;
        }
        if (posTartaruga <= 0)
            posTartaruga = 1;

        if (movimentoLebre >= 1 && movimentoLebre <= 5)
        {
            std::cout << "Sem base isso!!!\nA Lebre tá a 1000 km/h" << std::endl;
            posLebre += 7;
        }
        else if (movimentoLebre)
        {
            std::cout << "Opa, segura Peão!!" << std::endl;
            posLebre -= 2;
        }
        else
        {
            std::cout << "A Lebre tá andando lentamente" << std::endl;
            posLebre += 3;
        }
        if (posLebre <= 0)
            posLebre = 1;
        std::cout << "| TARTARUGA " << posTartaruga << " |Lebre " << posLebre << "|" << std::endl;
        std::cout << std::endl;
    }
    if (posTartaruga >= TAMANHO_PISTA && posLebre >= TAMANHO_PISTA)
    {
        std::cout << "Incrível, aconteceu um empate!!!" << std::endl;
    }
    else if (posTartaruga >= TAMANHO_PISTA)
    {
        std::cout << "Minha Nossa Senhora, a Tartaruga lenta desse jeito ganhou!!!" << std::endl;
    }
    else
    {
        std::cout << "A Lebre ganhou!!" << std::endl;
    }

    return 0;
}

int geraAleatorio(int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(a, b);
    return dist(gen);
}