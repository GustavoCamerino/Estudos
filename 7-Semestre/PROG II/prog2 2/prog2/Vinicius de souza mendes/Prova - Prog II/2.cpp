/*
Nesse exercício, você deve implementar o clássico jogo da velha 
bidimensional. Use um Array C++ 3x3 (matriz) para armazenar as jogadas. Cada jogador 
deve indicar suas jogadas inserindo um par de números inteiros representando os 
índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um 
'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado 
ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira 
uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém 
ganhou ou se houve empate. 
*/


#include <iostream>
#include <array>
#include <string>

int verifica_vencedor(std::array<std::array<std::string,3>,3>,std::string);


int main(){
    int cont{0};
    int x,y;
    //linder: inicializacao errada
    std::array<std::array<std::string,3>,3> jogo = {{"n","n","n"},{"n","n","n"},{"n","n","n"}};

    while(True){ //linder: true
        std::cout << "digite a posicao do jogador x" << std::endl;
        std::cin >> x >> y;

        while(jogo.at(x).at(y) != "n"){
            std::cout << "posicao ocupada digite novamente" << std::endl;
            std::cin >> x >> y;
        }
        jogo.at(x).at(y) = "x";
        cont++;

        if (verifica_vencedor(jogo,"x") == 1){
            std::cout << "jogador x venceu!!!!" << std::endl;
            break;
        }else if(cont >= 9) {
            std::cout << "empate!!!!" << std::endl; 
            break;
        }

        std::cout << "digite a posicao do jogador o" << std::endl;
        std::cin >> x >> y;

        while(jogo.at(x).at(y) != "n"){
            std::cout << "posicao ocupada digite novamente" << std::endl;
            std::cin >> x >> y;
        }
        jogo.at(x).at(y) = "o";
        cont++;

        if (verifica_vencedor(jogo,"o") == 1){
            std::cout << "jogador O venceu!!!!" << std::endl;
            break;
        }else if(cont >= 9) {
            std::cout << "empate!!!!" << std::endl; 
            break;
        }
    }
    return 0;
}

//linder: operacoes logicas erradas
int verifica_vencedor(std::array<std::array<std::string,3>,3> jogo,std::string jogador){
    //verifica horizontalmente
    if((jogo.at(0).at(0) = jogador) and (jogo.at(0).at(1) = jogador)  and (jogo.at(0).at(2) = jogador) ) return 1;
    else if((jogo.at(1).at(0) = jogador)  and (jogo.at(1).at(1) = jogador)  and (jogo.at(1).at(2) = jogador) ) return 1;
    else if((jogo.at(2).at(0) = jogador)  and (jogo.at(2).at(1) = jogador)  and (jogo.at(2).at(2) = jogador) ) return 1;
    // verifica verticalmente
    else if((jogo.at(0).at(0) = jogador)  and (jogo.at(1).at(0) = jogador)  and (jogo.at(2).at(0) = jogador) ) return 1;
    else if((jogo.at(0).at(1) = jogador)  and (jogo.at(1).at(1) = jogador)  and (jogo.at(2).at(1) = jogador) ) return 1;
    else if((jogo.at(0).at(2) = jogador)  and (jogo.at(1).at(2) = jogador)  and (jogo.at(2).at(2) = jogador) ) return 1;
    // verifica na diagonal
    else if((jogo.at(0).at(0) = jogador)  and (jogo.at(1).at(1) = jogador)  and (jogo.at(2).at(2) = jogador) ) return 1;
    else if((jogo.at(0).at(2) = jogador)  and (jogo.at(1).at(1) = jogador)  and (jogo.at(2).at(0) = jogador) ) return 1;
    else return 0;
}


