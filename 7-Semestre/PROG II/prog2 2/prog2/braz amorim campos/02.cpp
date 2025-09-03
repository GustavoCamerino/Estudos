#include <iostream>
#include <array>

const int col = 3;
const int lin = 3;

int main(){
    //Tabuleiro e uma Mtz de char 'o' ou 'x'
    std::array<std::array<char, col>, lin> tabuleiro {std::array<char, 3>{' ',' ',' '}, std::array<char, 3>{' ',' ',' '}, std::array<char, 3>{' ',' ',' '}};

    //Vars auxiliares
    int posJogLin {0}; 
    int posJogCol {0};
    bool vezJogador1 = true; 
    char jogada {' '};

    bool jogador1Venceu {false};
    bool jogador2Venceu {false};

    int contAcertos1{0};
    int contAcertos2{0};

    //INICIAR JOGO
    for(int i{0}; i < 9; i++){
        //Obter a jogada
        if (vezJogador1){
            std::cout << "[JOGADOR 1] Informe a jogada (linha x coluna): ";
            std::cin >> posJogLin >> posJogCol;
        }
        else{
            std::cout << "[JOGADOR 2] Informe a jogada: (linha x coluna)";
            std::cin >> posJogLin >> posJogCol;
        }
        
        //Determinar se a jogada e valida
        //Se sim Atualizar mtz
        if(tabuleiro.at(posJogLin).at(posJogCol) == ' '){ //Se a posicao estiver vazio
            //muda a vez para o prox jogador
            vezJogador1 = !vezJogador1; //linder: mudou a vez antes de atualizar

            //Se for o jogador 1, guardar 'X'
            if (vezJogador1){
                //Guardar jogada na posicao
                tabuleiro.at(posJogLin).at(posJogCol) = 'X';
            }
            //Se for o jogador 2, guardar 'O'
            else{
                //Guardar jogada na posicao
                tabuleiro.at(posJogLin).at(posJogCol) = 'O';
            } 
 
            //linder: essas verificacoes estao erradas!!
            
            //Verificar se alguem venceu:
            //Iterando (verificando) pelas colunas
            for(int j{0}; j < lin; j++){
                for(int i{0}; i < col; i++){
                    //Verificando acertos do jogador1
                    if(tabuleiro.at(i).at(j) == 'X'){
                        contAcertos1 ++;
                    }
                    //Verificando acertos do jogador2
                    if(tabuleiro.at(i).at(j) == 'O'){
                        contAcertos2 ++;
                    }
                }
                //Terminada a verificacao da coluna, verificar contAcertos
                if(contAcertos1 == 3){
                    jogador1Venceu = true;
                    break;
                }
                if(contAcertos2 == 3){
                    jogador2Venceu = true;
                    break;
                }

                //Resetar contAcertos
                contAcertos1 = 0;
                contAcertos2 = 0;
            }
            //Se alguem tiver vencido, encerra o jogo e mostra o vencedor
            if(jogador1Venceu){
                std::cout << "Jogador 1 venceu!" << std::endl;
                break;
            }
            else if(jogador2Venceu){
                std::cout << "Jogador 2 venceu!" << std::endl;
                break;
            }

            //Iterando (verificando) pelas linhas
            for(int i{0}; i < lin; i++){
                for(int j{0}; j < col; j++){
                    //Verificando acertos do jogador1
                    if(tabuleiro.at(i).at(j) == 'X'){
                        contAcertos1 ++;
                    }
                    //Verificando acertos do jogador2
                    if(tabuleiro.at(i).at(j) == 'O'){
                        contAcertos2 ++;
                    }
                }
                //Terminada a verificacao da coluna, verificar contAcertos
                if(contAcertos1 == 3){
                    jogador1Venceu = true;
                    break;
                }
                if(contAcertos2 == 3){
                    jogador2Venceu = true;
                    break;
                }

                //Resetar contAcertos
                contAcertos1 = 0;
                contAcertos2 = 0;
            }
            //Se alguem tiver vencido, encerra o jogo e mostra o vencedor
            if(jogador1Venceu){
                std::cout << "Jogador 1 venceu!" << std::endl;
                break;
            }
            else if(jogador2Venceu){
                std::cout << "Jogador 2 venceu!" << std::endl;
                break;
            }

            //Verificar diagonal principal
            for(int i{0}; i < lin; i++){
                //Verificando acertos do jogador1
                if(tabuleiro.at(i).at(i) == 'X'){
                    contAcertos1 ++;
                }
                //Verificando acertos do jogador2
                if(tabuleiro.at(i).at(i) == 'O'){
                    contAcertos2 ++;
                }
            }
            //Terminada a verificacao da diagonal, verificar contAcertos
            if(contAcertos1 == 3){
                jogador1Venceu = true;
            }
            if(contAcertos2 == 3){
                jogador2Venceu = true;
            }
            //Resetar contAcertos
            contAcertos1 = 0;
            contAcertos2 = 0;
            //Se alguem tiver vencido, encerra o jogo e mostra o vencedor
            if(jogador1Venceu){
                std::cout << "Jogador 1 venceu!" << std::endl;
                break;
            }
            else if(jogador2Venceu){
                std::cout << "Jogador 2 venceu!" << std::endl;
                break;
            }

            //Verificar diagonal secundaria
            int posCol {0};
            for(int i{0}; i < lin; i++){
                //Calculando a pos da coluna
                posCol = (col - 1) - i;

                //Verificando acertos do jogador1
                if(tabuleiro.at(i).at(posCol) == 'X'){
                    contAcertos1 ++;
                }
                //Verificando acertos do jogador2
                if(tabuleiro.at(i).at(posCol) == 'O'){
                    contAcertos2 ++;
                }
            }
            //Terminada a verificacao da coluna, verificar contAcertos
            if(contAcertos1 == 3){
                jogador1Venceu = true;
                break;
            }
            if(contAcertos2 == 3){
                jogador2Venceu = true;
                break;
            }
            //Resetar contAcertos
            contAcertos1 = 0;
            contAcertos2 = 0;
            //Se alguem tiver vencido, encerra o jogo e mostra o vencedor
            if(jogador1Venceu){
                std::cout << "Jogador 1 venceu!" << std::endl;
                break;
            }
            else if(jogador2Venceu){
                std::cout << "Jogador 2 venceu!" << std::endl;
                break;
            }

            //Se ninguem tiver vencido empate
            if(jogador1Venceu == false && jogador2Venceu == false) {
                std::cout << "Empate!" << std::endl;
            }
        }
        //Se a posicao estiver vazio, pedir outra entrada para o jogador atual
        else{ 
            std::cout << "Posicao ocupada, informe outra" << std::endl;
        }
    }

    //Se nenhum dos jogadores tiver vencido apos 9 rodadas
    if(jogador1Venceu == false && jogador2Venceu == false){
        std::cout << "Empate!" << std::endl;
    }

    return 0;
}