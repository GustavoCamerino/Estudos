#include <iostream>
#include <array>
#include <format>

/*Nesse exercício, você deve implementar o clássico jogo da velha 
bidimensional. Use um Array C++ 3x3 (matriz) para armazenar asjogadas. Cada jogador 
deve indicar suas jogadas inserindo um par de números inteiros representando os 
índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um 
'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado 
ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira 
uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém
ganhou ou se houve empate.*/

void Imprime_Matriz(const std::array<(std::array<char,3>),3>); //linder: nao tem esse ()
void Altera_Matriz(int X, int Y, std::array<(std::array<char,3>),3>& Matriz, int Jogador);
char Analisa_Vitoria(const std::array<(std::array<char,3>),3>& Matriz);

int main(){

    std::array<int,2> Jogador_1 = {0,0};
    std::array<int,2> Jogador_2 = {0,0};

    //linder: nao tem esses parenteses na declaracao
    std::array<(std::array<char,3>),3> Matriz= {{" "," "," "},{" "," "," "},{" "," "," "}};

    bool Vitoria = false;
    int Rodadas{0};
    int X1, Y1, X2, Y2;

    while(Vitoria == false){

        Rodadas++;
        std::cout << std::format("Rodada {}",Rodadas) << std::endl;

        std::cout << "Jogador 1" << std::endl;
        std::cout << "Determine a coordenada X: ";
        std::cin >> X1;
        std::cout << std::endl;
        std::cout << "Determine a coordenada Y: ";
        std::cin >> Y1;
        std::cout << std::endl;

        Altera_Matriz(X1, Y1, Matriz, 1);

        std::cout << "Jogador 2" << std::endl;
        std::cout << "Determine a coordenada X: ";
        std::cin >> X2;
        std::cout << std::endl;
        std::cout << "Determine a coordenada Y: ";
        std::cin >> Y2;
        std::cout << std::endl;

        Altera_Matriz(X2, Y2, Matriz, 2);

        Imprime_Matriz(Matriz);

    }

    return 0;
}

void Imprime_Matriz(const std::array<(std::array<char,3>),3> Matriz){

    for(const auto& Linha : Matriz){

        for(auto& Caractere : Linha){

            std::cout << std::format("{} ", Caractere);
        }

        std::cout << std::endl;

    }
}

//linder: nao entendi nada do porque dessa logica
void Altera_Matriz(int X, int Y, std::array<(std::array<char,3>),3>& Matriz, int Jogador){

    bool Linha_Certa = false;
    int Cont_Linha{0};
    int Cont_Num_Linha{0};

    for(const auto& Linha : Matriz){

        if(Cont_Linha == X){
            Linha_Certa = true;
        }

        for(auto& Caractere : Linha){

            if((Cont_Num_Linha == Y) && (Linha_Certa == true)){

                if(Jogador == 1){

                    Caractere = "O";

                }else if(Jogador == 2){

                    Caractere = "X";

                }
            }
        }

        Cont_Linha++;
        Cont_Num_Linha = 0;

    }
}

//Nao consegui completar :(
char Analisa_Vitoria(const std::array<(std::array<char,3>),3>& Matriz){

    char Caractere_Vencedor;
    //char Comparador = "-";
    int Cont_Linha{0};
    int Cont_Coluna{0};
    int Cont_Diagonal_1{0};
    int Cont_Diagonal_2{0};

     for(const auto& Linha : Matriz){

        for(auto& Caractere : Linha){

            if((Caractere == "X") || (Caractere == "O")){

                Cont_Linha++;

            }

            //Comparador = Caractere;
        }

        Comparador = "-";

    }

    if((Cont_Linha == 3) || (Cont_Coluna == 3) || (Cont_Diagonal_1 == 3) || (Cont_Diagonal_2 == 3)){

        return
    }
}