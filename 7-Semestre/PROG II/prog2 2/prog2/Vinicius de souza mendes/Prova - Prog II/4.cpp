/*
 Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio 
de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para 
isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma 
variável global. Crie a função int tentativa(int chute) que compara o chute do 
usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário 
chutou alto e -1 se o usuário chutou baixo. Use uma variável está ca para contar 
quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o 
jogador acerte, exiba também o total de tenta vas usadas. Caso o jogador erre, 
informe se o chute foi alto ou baixo. O programa deve permi r que o usuário con nue 
tentando até acertar.
*/

#include <iostream>
#include <random>

int tentativa(int);


std::random random_device rd;
std::random mt19937 gen(rd());
std::random uniform_int_distribution <int>dist(1,100);
int num_sort = dist(gen);

int main(){
    int entrada;
    int flag{1};

    while(flag != 0){
        std::cout << "chute um valor" << std::endl;
        std::cin >> entrada;
        flag = tentativa(entrada);
        if(flag == 1) std::cout << "chute muito alto" << std::endl;
        else std::cout << "chute muito baixo" << std::endl;
    }

    std::cout << "acertou!!!!!!" << std::endl;
    return 0;
}

int tentativa(int chute){
    static int quant{0};
    quant++;
    std::cout << "tentativa numero = " << quant << std::endl;
    if(chute > num_sort)return 1;
    if(chute < num_sort)return -1;
    return 0;
}



