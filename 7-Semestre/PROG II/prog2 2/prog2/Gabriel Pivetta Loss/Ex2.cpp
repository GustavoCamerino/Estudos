#include <array>
#include <iostream>
#include <string>
#include <vector>


int main() {

    //declaração de variaveis
    std::string mtz[3][3]; //linder: pedi com array c++
    int linha, coluna, jogadas, x_ou_o;
    bool ganhou {false};
    std::array <std::string, 2> simbolo {"X", "O"};
    std::vector<std::string> diagonal;
    std::vector<std::string> diagonal_inv;

    //valor máximo possivel de jogadas é 9
    jogadas = 0;

    //Inicialização da matriz
    for(int i{0}; i < 3; i++) {
        for(int j{0}; j < 3; j++) {
            mtz.at(i).at(j) = ""; //linder: errado! mtz é array c
        }
    }

    //enquanto ninguem ganhar ou empatar, o loop continuará
    while(!ganhou) 
    {
        std::cout << "Insira a linha e a coluna onde quer adicionar, seguido de qual simbolo marcar (0 para 'X' e 1 para 'O'): " << std::endl;

        do {
            std::cin >> linha >> coluna >> x_ou_o; //recebe o valor da linha, coluna e qual simbolo
            if(!(mtz.at(linha).at(coluna).empty())) { //verifica se a posição que o usuário escolheu não está vazia
                std::cout << "Posição já ocupada, insira novamente: " << std::endl;
            }
        } while(!(mtz.at(linha).at(coluna).empty())); //enquando não for uma entrada válida, continuará repetindo

        mtz.at(linha).at(coluna) = simbolo.at(x_ou_o); //insere o simbolo na matriz na posição que o usuário escolheu

    //para verificar se a diagonal foi preenchida, e se todos os valores nela são iguais
    
        if(linha == coluna) {
            diagonal.push_back(mtz[linha][coluna]);
            if(diagonal.size() == 3) {
                if (diagonal[0] == diagonal[1] && diagonal[1] == diagonal[2]) ganhou = true;
            }
        } 
    //para verificar se a diagonal da direita pra esquerda foi totalmente preenchida, e se todos os valores nela são iguais
        else if((linha == coluna) || (linha == 0 && coluna == 2) || (linha = 2 && coluna == 0)) {
            diagonal_inv.push_back(mtz[linha][coluna]);
            if(diagonal_inv.size() == 3) {
                if(diagonal_inv[0] == diagonal_inv[1] && diagonal_inv[1] == diagonal[2]) ganhou = true;
            }
        }
    
        //para verificar as linhas e colunas
        for (int l = 0; l < 3; l++) {
            if(mtz[l][0] == mtz[l][1] && mtz[l][1] == mtz[l][2]) { //se todos da mesma linha forem iguais, ganhou = true
                ganhou = true;
            }
            for (int m = 0; m < 3; m++) {

                if(mtz[0][m] == mtz[1][m] && mtz[1][m] == mtz[2][m]) { //se todos da coluna forem iguais, ganhou = true
                ganhou = true;

                } 
            }
        }
        //se ninguem ganhou nessa iteração, aumenta o numero de jogadas
        jogadas++;
        if(jogadas == 9) {
            std::cout << "Temos um empate!" << std::endl;
            break;
        }
    }

    if(ganhou) {
        std::cout <<"Temos um vencedor!" << std::endl;
    }

    return 0;
}