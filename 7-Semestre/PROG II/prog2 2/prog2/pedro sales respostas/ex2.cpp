#include <iostream>
#include <format>
#include <array>
#include <string>

//PROTOTIPOS DE FUNCAO
void mostra_jogo(const std::array<std::array<char,3>,3> &jogo_atual);
int verifica_jogo(const std::array<std::array<char,3>,3> &jogo_atual);
bool jogada_valida(const std::array<std::array<char,3>,3> &jogo_atual ,int l , int c);


int main(){

    //inicializando o arraty 3x3 vazio
    //linder: erro na inicializacao
    std::array<std::array<char,3>,3> jogo_da_velha {std::array{'','',''},std::array{'','',''},std::array{'','',''}};
    
    //variavel string para definir qual jogador esta jogando
    std::string jogador_atual ;


    //define em qual rodada estamos comecando pelo jogador A que joga com o X ele joga nas rodadas impares
    //enquando o jogador do simbolo O joga nas jogadas pares
    int rodada{1} ;

    //variavel para armazenar a situacao do jogo
    int situacao{3};
    
    //variaveis para armazenar as entradas dos jogadores
    int linha , coluna ;
    
    while(situacao == 3){
        
        if(rodada%2 == 0){
            jogador_atual = "JOGADOR A" ;
        }
        else{
            jogador_atual = "JOGADOR B" ;
        }

        do{
        std::cout << std::format("\n{}\n",jogador_atual) ;
        std::cout << "Faca uma jogada : \n" ;
        std::cout << "linha:\n"
        std::cin >> linha ;
        std::cout << "coluna:\n"
        std::cin >> coluna ;
        }while(jogada_valida(jogo_da_velha,linha,coluna) == false); 
        if(rodada%2 == 0){
            jogo_da_velha.at(linha).at(coluna) = 'O' ;
            situacao = verifica_jogo(jogo_da_velha) ;            
        }
        
        else{
            jogo_da_velha.at(linha).at(coluna) = 'X' ;
            situacao = verifica_jogo(jogo_da_velha) ;            
        }

        mostra_jogo(jogo_da_velha);
        rodada++ ;
    }
    if(situacao == 1){
        std::cout << "JOGADOR A GANHOU !!\n" ;
    }
    else if(situacao == 2){
        std::cout << "JOGADOR B GANHOU !!\n" ;        
    }
}


//linder: sua logica de verificacao nao parece funcionar
int verifica_jogo(const std::array<std::array<char,3>,3> &jogo_atual){
    //contadores 
    int conta_linha_x {0} ;
    int conta_linha_o {0} ;
    int conta_coluna_x{0} ;
    int conta_coluna_o{0} ;
    int conta_diagonal_principal_x{0} ;
    int conta_diagonal_principal_o{0} ;    

    for(int i{0} ; i<3; i++){
        conta_linha_o = 0 ;
        conta_linha_x = 0 ;
        conta_coluna_o = 0 ;
        conta_coluna_x = 0  
        for (int j{0} ; j <3 ; j++){
            
            //verificando linhas
            if(jogo_atual.at(i).at(j) == 'X'){ //linder: erro de sintaxe
                conta_linha_x++;
            }
            else if(jogo_atual.at(i).at(j) == 'O'){
                conta_linha_o++;
            }
            
            //verificando colunas
            if(jogo_atual.at(j).at(i) == 'X'){
                conta_coluna_x++ ;
            }
            else if(jogo_atual.at(j).at(i) == 'O'){
                conta_coluna_o++ ;
            }

            //verificando elementos da diagonal pricipal
            if(i == j){
                if(jogo_atual.at(i).at(j) == 'X'){
                    conta_diagonal_principal_x++;
                }
                else if(jogo_atual.at(i).at(j) == 'O'){
                    conta_diagonal_principal_o++;
                }
            }

            //verificando condicao de vitoria em linhas e colunas(3 simbolos iguais consecutivos)
            if(conta_linha_x == 3){
                return 1 ;
            }

            else if(conta_linha_o == 3){
                return 2 ;
            }

            if(conta_coluna_x == 3){
                return 1 ;
            }

            else if(conta_coluna_o == 3){
                return 2 ;
            }
            
        }
    }

//verificando diagonal segundaria
    if(jogo_atual.at(0).at(2) == 'X' && jogo_atual.at(1).(1) == 'X' && jogo_atual.at(2).(0) == 'X'){
        return 1 ;
    }

    else if(jogo_atual.at(0).at(2) == 'O' && jogo_atual.at(1).(1) == 'O' && jogo_atual.at(2).(0) == 'O'){
        return 2 ;
    }

    return 3 ;
}


void mostra_jogo(const std::array<std::array<char,3>,3> &jogo_atual){
    for(const std::array<char,3>& linha : jogo_atual){
        for(const char espaco : linha){
            std::cout << std::format("|{}|",espaco);
        }
        std::cout << "\n";
    }
}
    
bool jogada_valida(const std::array<std::array<char,3>,3> &jogo_atual ,int l , int c){
    if(jogo_atual.at(l).at(c) == ''){
        return true ;
    }else{
        return false ;
    }
}

