#include <iostream>
#include <random>

// Prototipos
int geraAleatorio(int a, int b);
void jogo();

int main(int argc, char const *argv[])
{
    jogo();
    return 0;
}

int geraAleatorio(int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(a, b);
    return dist(gen);
}

void jogo()
{
    int gamestatus{0};
    std::cout << "Digite 1 para jogar: ";
    std::cin >> gamestatus;

    while (gamestatus == 1)
    {
        int number = geraAleatorio(1, 1000);
        int chute{0};
        std::cout << "Adivinhe um número entre 1 e 1000: ";
        std::cin >> chute;
        if (chute == number)
        {
            std::cout << "Parabéns, você acertou o número!!!" << std::endl;
            std::cout << "Quer jogar de novo?\nSe sim digite 1 | Se não digite qualquer número: ";
            std::cin >> gamestatus;
        }
        else if (chute > number)
        {
            std::cout << "Muito Alto" << std::endl;
            chute = 0;
            std::cout << "Quer jogar de novo?\nSe sim digite 1 | Se não digite qualquer número: ";
            std::cin >> gamestatus;
        }
        else if (chute < number)
        {
            std::cout << "Muito Baixo" << std::endl;
            std::cout << "Quer jogar de novo?\nSe sim digite 1 | Se não digite qualquer número: ";
            std::cin >> gamestatus;
        }
    }
    std::cout << "Jogo Finalizando\nObrigado por Jogar\n";
}