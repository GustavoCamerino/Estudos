// Prova 1
// Danilo Barbosa da Silva
// Questão 4

#include <iostream>
#include <random>


// Prototipo
int tentativa_func(int chute);

int main () {
    // Gerador de valores
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::uniform_int_distribution<int> geraInt(1, 100);
    
    // Variavel Global (Numero Secreto)
    global int numero_secreto = geraInt(engine); //linder: "global" nao existe
    
    int chute{0};
    bool flag{true};
    int tentativa{0};

    std::cout << "(Jogo da Adivinhação) chute um valor entre 1 e 100: " << std::endl;

    // Laco que controle do jogo
    while(flag) {
        std::cin >> chute;
        tentativa = tentativa_func(chute);
        if(tentativa == -1) {

            std::cout << "Muito Baixo Tente Novamente" << std::endl;

        } else if(tentativa == 1) {

            std::cout << "Muito alto Tente Novamente" << std::endl;

        } else if(tentativa == 0) {

            std::cout << "Parabens Você Acertou !!!" << std::endl;

            flag = false; 
        }
    }


    return 0;
}


// Testa o se o chute está correto
int tentativa_func(int chute) {
    static int contador{0}; 
    contador ++;
    if(chute < numero_secreto) {
        return -1;
    }
    if(chute > numero_secreto) {
        return 1;
    } else {
        // Exibe o numero de tentativas
        std::cout << "Tentativas: "<< contador << std::endl;
        return 0;
    }
}





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