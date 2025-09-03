#include <iostream>
#include <random>

std::random_device seed;
std::default_random engine{seed()}; //linder: default_random_engine engine
std::uniform_int_distribution generator{1, 100};
int numeroSecreto = generator(engine);

int tentativa(int chute);

int main(){
    int resultado{1};
    int chute{0};
    std::cout << "Informe valores para tentar advinhar o numero secreto que está entre 1 e 100" << std::endl;
    while(resultado != 0){
        std::cin >> chute;
        resultado = tentativa(chute);
        if (resultado == 1){
            std::cout << "Muito alto" << std::endl;
        } else if(resultado == -1){
            std::cout << "Muito baixo" << std::endl;
        }
    }
    std::cout << "Parabéns! Acertou!" << std::endl;
    return 0;
}

int tentativa(int chute){
    static int quantidadeTentativas{0};
    quantidadeTentativas++;
    if (chute == numeroSecreto){
        std::cout << "Quantidade de tentativas: " << quantidadeTentativas << std::endl;
        return 0;
    } else if (chute < numeroSecreto){
        return -1;
    } else if (chute > numeroSecreto){
        return 1;
    }
}