#include <iostream>
#include <random>

int numeroSecreto {0};
int tentativa(int chute);

int main(){
    //Setup Numeros aleatorios
    std::random_device seed;
    std::default_random_engine engine{seed()};
    std::uniform_int_distribution distribution {1, 100};

    //Vars auxiliares
    bool continuar = true;
    int retornoTentativa {-2};
    int chute {-2};

    while(continuar){
        //Gerar numero secreto
        numeroSecreto = distribution(engine); //linder: errado, deveria sortear uma vez!

        //Obter tentativa
        std::cout << "Chute um numero entre 1 e 100: ";
        std::cin >> chute;

        //Obter resultado da tentativa
        retornoTentativa = tentativa(chute);

        //Encerra o jogo se o jogador acertou
        continuar = (retornoTentativa == 0) ? false : true; 
    }

    return 0;
}

//linder: nao implementou como solicitado!
int tentativa(int chute){
    int retorno {-2};
    //Variavel estatica pois sua inicializacao ocorre apenas uma vez
    static int quantTentativas {0};

    //Como houve chamada da funcao (tentativa) incrementar
    quantTentativas ++;

    if(chute == numeroSecreto){
        retorno = 0;
        std::cout << "Chute correto! /n"; //linder: nunca alcancado
        std::cout << "Quantidade de tentativas: " << quantTentativas << std::endl;
    }
    else if(chute < numeroSecreto){
        retorno = -1;
        std::cout << "Chutou baixo! /n"; //linder: nunca alcancado
    }
    else if(chute > numeroSecreto){
        retorno = 1;
        std::cout << "Chutou alto! /n"; //linder: nunca alcancado
    }

    return retorno;
}