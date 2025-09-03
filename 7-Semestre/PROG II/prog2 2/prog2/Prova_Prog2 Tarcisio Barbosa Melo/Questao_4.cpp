#include <iostream>
#include <format>
#include <random>

/*(2.5 pts) Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio 
de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para 
isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma 
variável global. Crie a função int tentativa(int chute) que compara o chute do 
usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário 
chutou alto e -1 se o usuário chutou baixo. Use uma variável está+ca para contar 
quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o 
jogador acerte, exiba também o total de tentaBvas usadas. Caso o jogador erre, 
informe se o chute foi alto ou baixo. O programa deve permiBr que o usuário conBnue 
tentando até acertar.*/

int Gerar_Aleatorio(std::default_random_engine Gerador);
int Tentativa(int chute);

void Cabecalho();

//Variável global
std::default_random_engine Semente;
int Numero_Secreto = Gerar_Aleatorio(Semente);

int main(){

    Cabecalho();
    int Validacao;
    int Num_Tentativas{0};

    do{
        Num_Tentativas++; //linder: pedi como uma variavel estatica em tentativa

        std::cout << std::format("Tentativa {}", Num_Tentativas);
        std::cout << std::endl;

        int Chute;
        std::cout << "Faca um chute: ";
        std::cin >> Chute;
        std::cout << std::endl;

        Validacao = Tentativa(Chute);

    }while(Validacao != 0);


    return 0;
}

int Gerar_Aleatorio(std::default_random_engine Gerador){

    std::uniform_int_distribution<int> Alcance(1, 100);

    int Numero = Alcance(Gerador);

    return Numero;
}

int Tentativa(int chute){

    if(chute == Numero_Secreto){

        std::cout << "PARABENS VOCE ACERTOU!" << std::endl;

        return 0;

    }else if(chute > Numero_Secreto){

        std::cout << "O chute foi maior que o numero secreto." << std::endl;

        return 1;

    }else{

        std::cout << "Ochute foi menor que o numero secreto." << std::endl;

        return -1;

    }

}

void Cabecalho(){

    std::cout <<"------------------------------" << std::endl;
    std::cout <<"      JOGO DA ADVINHACAO      " << std::endl;
    std::cout <<"------------------------------" << std::endl;
    std::cout << std::endl;

}