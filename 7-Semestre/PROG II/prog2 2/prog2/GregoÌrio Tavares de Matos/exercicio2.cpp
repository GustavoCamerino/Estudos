#include <iostream>
#include <array>

int main(){
    //linder: inicializacao errada
    //jogo da velha 
    std::array<std::array<char, 3>, 3> matriz {{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}}; //array de caracteres vazio
    
    std::cout << "Jogador 1: x" << std::endl;
    std::cout << "Jogador 1: o" << std::endl;

    //jogo iniciado

    int vitoriaJogador1{0}; //flag que indica que jogador 1 venceu
    int vitoriaJogador2{0}; //flag que indica que jogador 2 venceu
    int vezDoJogador{1}; //indica o de qual jogador é o turno
    int l{0}; //posicao que o jogador escolhera para linha
    int c{0}; //posicao que o jogador escolhera para coluna
    int i{0}; //percorrer linhas da matriz
    int j{0}; //percorrer colunas da matriz

    while (vitoriaJogador1 == 0 && vitoriaJogador2 == 0){
        if (vezDoJogador == 1){
            std::cout << "informe a posicao da linha e da coluna da matriz respectivamente para marcar o 'x'" << std::endl;
            std::cin >> l >> c;
            if (matriz[l][c] != ' '){ //caso a posicao nao esteja vazia
                std::cout << "Posicao invalida." << std::endl;
            } else {
                matriz[l][c] = 'x';
                vezDoJogador = 2; //passa a vez para o jogador 2
            }
        } else if (vezDoJogador == 2){
            std::cout << "informe a posicao da linha e da coluna da matriz respectivamente para marcar o 'o'" << std::endl;
            std::cin >> l >> c;
            if (matriz[l][c] != ' '){ //caso a posicao nao esteja vazia
                std::cout << "Posicao invalida." << std::endl;
            } else {
                matriz[l][c] = 'o';
                vezDoJogador = 1; //passa a vez para o jogador 1
            }
        }

        //mostrando matriz
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                std::cout << matriz[i][j] << ' ' << std::endl;
            }
            std::cout << std::endl;
        }

        //conferindo se o jogo se encerrou ou nao

        //jogador1
        //conferindo linhas da matriz
        for (i = 0; i < 3; i++){
            if (matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2] && matriz[i][0] == 'x'){
                vitoriaJogador1 = 1;
                break;
            }
        }

        //conferindo colunas da matriz
        for (j = 0; j < 3; j++){
            if (matriz[0][j] == matriz[1][j] && matriz[1][j] == matriz[2][j] && matriz[0][j] == 'x'){
                vitoriaJogador1 = 1;
                break;
            }
        }

        //conferindo diagonais da matriz
        if (matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2] && matriz[0][0] == 'x'){
            vitoriaJogador1 = 1;
            break;
        }

        if (matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0] && matriz[0][2] == 'x'){
            vitoriaJogador1 = 1;
            break;
        }

        //jogador2
        //conferindo linhas da matriz
        for (i = 0; i < 3; i++){
            if (matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2] && matriz[i][0] == 'o'){
                vitoriaJogador2 = 1;
                break;
            }
        }

        //conferindo colunas da matriz
        for (j = 0; j < 3; j++){
            if (matriz[0][j] == matriz[1][j] && matriz[1][j] == matriz[2][j] && matriz[0][j] == 'o'){
                vitoriaJogador2 = 1;
                break;
            }
        }

        //conferindo diagonais da matriz
        if (matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2] && matriz[0][0] == 'o'){
            vitoriaJogador2 = 1;
            break;
        }

        if (matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0] && matriz[0][2] == 'o'){
            vitoriaJogador2 = 1;
            break;
        }

        //caso de empate
        int empate{1}; //considerando que o empate esta dado
        for (i = 0; i < 3; i++){
            for (j = 0; j < 3; j++){
                if (matriz[i][j] == ' '){
                    empate == 0; //linder: =
                }
            }
        }
        if (empate == 1){
            std::cout << "Deu velha! Empate!" << std::endl;
            return 0;
        }
    }

    if (vitoriaJogador1 = 1){ //linder: ==
        std::cout << "Jogador 1 venceu!" << std::endl;
    } else if (vitoriaJogador2 = 1){ //linder: ==
        std::cout << "Jogador 2 venceu!" << std::endl;
    }
    return 0;
}
