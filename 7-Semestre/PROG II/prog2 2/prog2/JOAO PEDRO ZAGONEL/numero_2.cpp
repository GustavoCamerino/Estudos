#include <iostream>
#include <array>
#include <string>

//linder: numero demasiado de erros!


int gravar(int i, int j, char jogador);
array jogo(int i, int j, char jogador); //linder: errado
array tabuleiro(int i, int j, char jogador);
int ganhador(std::array<std::array<char, [3]><char, [3]> Tabuleiro); //linder: errado



//  (3.0 pts) Nesse exercício, você deve implementar o clássico jogo da velha
//  bidimensional. Use um Array C++ 3x3 (matriz) para armazenar asjogadas. Cada jogador
//  deve indicar suas jogadas inserindo um par de números inteiros representando os
//  índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um
//  'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado
//  ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira
//  uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém
//  ganhou ou se houve empate.


std::array<std::array<char, [3]><char, [3]> Tabuleiro {{0, 0, 0},
                                                       {0, 0, 0}, 
                                                       {0, 0, 0}};

array jogo(int i, int j, char jogador){
    int p{i};
    int q{j};
    char player{jogador};

    if (p >= 0 || p <= 2){
        if (q >= 0 || q <= 2){
            if (player == "O"){
                gravar(p, q, player);
            }
            else if (player == "O"){
                gravar(p, q, player);
            }
        }
            else{
                std::cout << "Valores invalidos" << std::endl;
                return main();
        }
    }

    else{
        std::cout << "Valores invalidos" << std::endl;
        return main();
    }

    


}

int gravar(int i, int j, char jogador){
    int m{i}; int n{j};

    if (Tabuleiro.at(m, n) == 0){
        tabuleiro(m, n, jogador);
    }
    if else ((int m > 2 || int m < 0) || (int n > 2 || int n < 0)) {
        std::cout << "Posição invalida\n";
        return main();
    }
}

array tabuleiro(int i, int j, char jogador){
    std::array<std::array<char, [3]><char, [3]> Tabuleiro {{0, 0, 0},
                                                           {0, 0, 0}, 
                                                           {0, 0, 0}};

    for (int m = o; m < 3; m++){
        for (int n = 0; n < 3; n--){
            char atual = Tabuleiro[m][n];
            std::cout << atual << std::endl;
        }
    }                                                    


    Tabuleiro.at(i, j) = jogador;


    for (int m = o; m < 3; m++){
        for (int n = 0; n < 3; n--){
            char atual = Tabuleiro[m][n];
            std::cout << atual << std::endl;
        }
    }

    ganhador(Tabuleiro);

}

int ganhador(std::array<std::array<char, [3]><char, [3]> Tabuleiro){
    bool q1 = Tabuleiro[0][0] == Tabuleiro[0][1] == Tabuleiro[0][2];
    bool q2 = Tabuleiro[1][0] == Tabuleiro[1][1] == Tabuleiro[1][2];
    bool q3 = Tabuleiro[2][0] == Tabuleiro[2][1] == Tabuleiro[2][2];
    bool q4 = Tabuleiro[0][0] == Tabuleiro[1][1] == Tabuleiro[2][2];
    bool q5 = Tabuleiro[2][0] == Tabuleiro[1][1] == Tabuleiro[0][2];
    bool q6 = Tabuleiro[0][0] == Tabuleiro[1][0] == Tabuleiro[2][0];
    bool q7 = Tabuleiro[0][1] == Tabuleiro[1][1] == Tabuleiro[2][1];
    bool q8 = Tabuleiro[0][2] == Tabuleiro[1][2] == Tabuleiro[2][2];

    if (q1 == 1){
        jogador = Tabuleiro[0][0];
        if (jogador == "O"){
            std::cout << "Vencedor é o jogador das bolas!\n" std:endl;
        }
        else{
            std::cout << "Vencedor é o jogador dos XXXX!\n" std:endl;

        }

    }
    return main();
}

int main(){
    char jogador;
    int num1;
    int num2;


    std::cout << "Escolha sua jogada ( dois inteiros dos incices da matriz [linha][coluna]) de enter entre os valores nos valores, em seguida no jogador ( "X" ou "O"))" << std::endl;
    std::cin >> jogador;
    std::cin >> num1;
    std::cin >> num2;

    jogo(num1, num2, jogador);
}





