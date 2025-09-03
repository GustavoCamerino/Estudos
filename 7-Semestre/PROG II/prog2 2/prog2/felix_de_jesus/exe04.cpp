//Felix de jesus sousa Barros
/*4. (2.5 pts) Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio
de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para
isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma
variável global. Crie a função int tentativa(int chute) que compara o chute do
usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário
chutou alto e -1 se o usuário chutou baixo. Use uma variável está+ca para contar
quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o
jogador acerte, exiba também o total de tentaBvas usadas. Caso o jogador erre,
informe se o chute foi alto ou baixo. O programa deve permiBr que o usuário conBnue
tentando até acertar.*/

//linder: não fez nada do que eu pedi.

#include <iostream>
#include <random>

int numeroSecreto = 34;

int tentativa(int chute){
    for (int chute == numeroSecreto) {
        std::cout <<"Parabéns vc acertou!!! \n";
        return 0;
    }
    for (int chute < numeroSecreto) {
        std::cout <<"Você chutou baixo!!! \n";
        return -1;
    }
    for (int chute > numeroSecreto) {
        std::cout <<"Você chutou Alto!!! \n";
        return 1;
    } 

   } 

int main() {
    
    int chute;

    std:: cout <<"\nJogo da Adivinhação"<<std::endl;
    std:: cout <<"Digite um número inteiro entre (1 a 100)\n:"<<std::endl;
    std:: cin >> chute;

    if (int chute > 100 && int chute < 1) {
        std::cout <<"O número deve estar entre 1 e 100\n";
    } else {
        if (int chute != int numeroSecreto ){
           return int tentativa(int chute);  
        }     
    }      

    return 0;

}