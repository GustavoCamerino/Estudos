#include <iostream>
#include <random>
#include <format>

// Prototipacao e declaracao de variavel global

int tentativa(int chute);

int numero_secreto {0};


int main()
{
    // Para gerar numeros randomicos
    std::random_device seed;
    std::default_random_engine engine{seed()};
    std::uniform_int_distribution gerador{1,100};

    // Atribuindo um numero randomico para variavel global
    numero_secreto = gerador(engine);

    // Variaveis para controlar o jogo e receber o numero do usuario
    int flag {1};
    int numero_usuario {0};

    //linder: nao implementou como pedido
    do{
        // Recebendo o numero do usuario 
        std::cout << "Insira um numero na faixa de 1 a 100: ";
        std::cin >> numero_usuario;

        // Variavel estatica para contabilizar o numero de tentativas
        static int tentativas {0}; 

        // Cada chamada da funcao deve aumentar o contador de tentativas
        int result = tentativa(numero_usuario);
        tentativas++;

        // Retorno da funcao = 1
        if(result == 1){
        // Usuario deu um chute muito alto
            std::cout << "\nChute muito alto. Tente novamente";
            flag = 1;
        } 
        // Retorno da funcao -1
        if else (result == -1){ //linder: erro
        // Usuario deu um chute muito baixo
            std::cout <<"\nChute muito baixo. Tente novamente";
            flag = 1;
        } 
        // Retorno da funcao 0
        if else(result == 0){
        // Usuario acertou o numero secreto (Informar o numero de tentativas)
            std::cout << std::format("\nVoce acertou. Tentativas usadas: {}", tentativas);
            flag = 0;
        }
    } while(flag);

    return 0;
}

// Definicao da funcao
int tentativa(int chute)
{
    if(numero_secreto > chute){
        return -1;
    } if else(numero_secreto < chute){
        return 1;
    } else {
        return 0;
    }
}