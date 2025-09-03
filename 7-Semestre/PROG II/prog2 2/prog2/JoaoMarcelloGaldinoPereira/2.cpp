#include <iostream>
#include <array>
#include <format>

// Prototipo

//linder: apresenta varios erros
int VerificaMtz(std::array<std::array<char,3>,3> &mtz);

int main()
{
    std::array<std::array<char,3>,3> matriz {}; // matriz 3x3
    char jogador {'0'}; // Variavel para receber a entrada do jogador 

    // Laco para preencher a matriz com o char '0'
    for(int i {0} ; i < 3 ; i++){
        for(int j {0} ; j < 3 ; j++){
            matriz[i][j] = '0';
        }
    }

    int flag {1}; // flag para controlar o jogo
    int linha {0}; // Variavel para receber o numero da linha que o jogador deseja inserir
    int coluna {0}; // Variavel para receber o numero da coluna que o jogador deseja inserir

    while(flag){
        // Recebendo a posicao que o usuario deseja inserir 
        std::cout <<"Em qual posicao voce deseja inserir sua jogada: ";
        std::cin >> linha >> coluna;

        // laco para verificar se a posicao desejada ja tem um elemento e para inserir o elemento em uma posicao valida
        do{
            int flag1 {0};
            // Se a posicao desejada for diferente de '0' (Matriz foi iniciada com esse elemento para representar uma posicao vazia)
            if(matriz[linha][coluna] != '0'){
                std::cout << "\nEssa posicao ja esta ocupada: ";
                std::cin >> linha >> coluna;
                flag1 = 1;
            } // Pergunta se o jogador deseja inserir X ou O na posicao valida
                else {
                std::cout << std::format("O jogador deseja inserir \'X\' ou \'O\' na posicao [{}][{}]: ",linha,coluna);
                std::cin >> jogador1;
                matriz[linha][coluna] = jogador;
            }
        } while(flag1);
    int verifica = VerificaMtzVazio(matriz);

    // A matriz ainda nao foi completamente preenchida
    if(verifica == 0){
        flag = 1;
    } 
    // A matriz ja foi completamente preenchida
    if else (verifica == 1){
        // Verificando se o jogo teve um ganhadou ou rolou empate
        if(matriz[0][0] == 'X' && matriz[0][1] == 'X' && matriz[0][2] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else (matriz[0][0] == 'O' && matriz[0][1] == 'O' && matriz[0][2] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        }
        if else(matriz[1][0] == 'X' && matriz[1][1] == 'X' && matriz[1][2] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else(matriz[1][0] == 'O' && matriz[1][1] == 'O' && matriz[1][2] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        }
        if else(matriz[2][0] == 'X' && matriz[2][1] == 'X' && matriz[2][2] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else(matriz[2][0] == 'O' && matriz[2][1] == 'O' && matriz[2][2] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][0] == 'X' && matriz[1][0] == 'X' && matriz[2][0] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][0] == 'O' && matriz[1][0] == 'O' && matriz[2][0] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][1] == 'X' && matriz[1][1] == 'X' && matriz[2][1] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][1] == 'O' && matriz[1][1] == 'O' && matriz[2][1] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][2] == 'X' && matriz[1][2] == 'X' && matriz[2][2] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][2] == 'O' && matriz[1][2] == 'O' && matriz[2][2] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][0] == 'X' && matriz[1][1] == 'X' && matriz[2][2] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else(matriz[0][0] == 'O' && matriz[1][1] == 'O' && matriz[2][2] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        }
        if else(matriz[2][0] == 'X' && matriz[1][1] == 'X' && matriz[0][2] == 'X'){
            std::cout << "\nO jogador que estava usando \'X\' ganhou.";
            flag = 0;
        }
        if else(matriz[2][0] == 'O' && matriz[1][1] == 'O' && matriz[0][2] == 'O'){
            std::cout << "\nO jogador que estava usando \'O\' ganhou.";
            flag = 0;
        } else{
            std::cout << "\n O jogo empatou.";
            flag = 0;
        }
    }

    }
    return 0;
}

// Definicao da funcao
// Funcao para verificar se a matriz tem espaco para ser preenchido
int VerificaMtz(std::array<std::array<char,3>,3> &mtz)
{
    int retorno {0};
    for(const auto &linha : mtz){
        for(const auto &elemento : linha){
            if(elemento != '0'){ //linder: nao funciona
                retorno = 0;
                break;
            } else {
                retorno = 1;
            }
        }
    }
    return retorno;
}