#include <iostream>
#include <format>
#include <vector>

using namespace std;

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

int main(){

    array<char, 3>, 3> matriz; //linder: Nao sabe definir matriz

    int linha
    int coluna;
    char marca;

    cout << "Digite a linha e coluna da posicao em que voce quer marcar(ex: linha coluna): (ex: 1 3)\n";
    cin >> linha >> coluna;

    cout << "Digite \"X\" ou \"O\": ";
    cin >> marca;
    
    //linder: nao faz nada do que foi pedido!
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){

            if (matriz.at(i) == 'X'){
                cout << "Já está ocupada por X,";
            }

            cout << "Digite \"X\" ou \"O\"" << endl;
            cin >> matriz.at([i][j]); //indexacoes erradas

        }
    }

    return 0;
}