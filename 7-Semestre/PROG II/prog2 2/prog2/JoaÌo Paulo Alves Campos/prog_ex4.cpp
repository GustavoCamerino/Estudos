#include <iostream>
#include <random>

// Prova 1
// Programação 2
// 13/08/2025
// Aluno:João Paulo Alves Campos
// (2.5 pts) Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio
// de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para
// isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma
// variável global. Crie a função int tentativa(int chute) que compara o chute do
// usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário
// chutou alto e -1 se o usuário chutou baixo. Use uma variável está+ca para contar
// quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o
// jogador acerte, exiba também o total de tentaBvas usadas. Caso o jogador erre,
// informe se o chute foi alto ou baixo. O programa deve permiBr que o usuário conBnue
// tentando até acertar.
static int numero_secreto{randomizar}

//linder: cheio de erro
int randomizar(){
    static std::random_device rd(); //errado
    static std::mt19997 gen(rd());  //linder: nunca usamos isso
    static std::uniform_int_distribution<int> dist(1,100);
    return numero_secreto = dist(gen());
}
int tentativa(int chute){
    static int contador{0};
    if(chute<numero_secreto){
        std::cout << "Voce chutou baixo... " << std::endl;
        contador++;
        return -1;
    }
    if(chute>numero_secreto){
        std::cout << "Voce chutou alto... " << std::endl;
        contador++;
        return 1;
    }
    else{
        std::cout << "Parabens você acertou o numero secreto, e voce persistiu por: " << contador << "Vezes." << std::endl;
        contador=0; 
        return 0;
    }
}

int main(){
    std::cout << "Adivinhe um numero de 0 a 100" << endl;
    int continuar{1}
    int chute;
    while(continuar==1){
        std::cout << "Adivinhe um numero de 0 a 100" << endl;
        std::cin >> chute;
        if(tentativa(chute) == 0 ){
            std::cout << "Deseja continuar? digite 1 para continuar e qualquer outra para finalizar" << std::endl;
            std::cin >> continuar;
            if(continuar == 1){
                randomizar();
                continue;
            }
            else{
                break;
            }
        }
    }
    std::cout << "obrigado por jogar!!" << std::endl;
    return 0;
}

//acho que esta ok