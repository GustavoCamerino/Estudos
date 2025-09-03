#include <iostream>
#include <array>
using namespace std;

// linder: no primeiro exercicio todas as definicoes em portugues
// linder: mudou completamente o estilo de nomear
void printBoard(const <array<array<char,3>,3>& b){ //linder: sintaxe errada
    cout << "\n 1 2 3\n";
    for(int i = 0; i < 3; i++){ //linder: inicializacao estilo c
        cout << i+1 <<'';       
        for(int j = 0; j < 3; ++j){
            char c = b[i][j];
            if(c == 0) cout << ".";   //linder: comando if-else errado
            else cout << c;
            if(j < 2) cout << "";
        }
        cout << '\n';


         // linder: espacamento suspeito



    }

        // linder: espacamento suspeito


}

// linder: mudou completamente o estilo de nomear
bool checkWin(const array<array<char,3>,3>& b, char p){
    for(int i = 0 ;i<3; i++){ //linder: inicializacao estilo c
        if(b[i][0]==p && b[i][1]==p && b[i][2]==p) return true;
        if(b[0][i]==p && b[1][i]==p && b[2][i]==p) return true;
    }
    
    if(b[0][0]==p && b[1][1]==p && b[2][2]==p) return true;
    if(b[0][2]==p && b[1][1]==p && b[2][0]==p) return true;
    return false;


}

// linder: mudou completamente o estilo de nomear
bool boardFull(const array<array<char,3>,3>& b){ //linder: inicializacao estilo c
    for(int i = 0;i<3;++i)for(int j = 0;j<3; ++j) if(b[i][j] == 0) return false;
    return false;
}

//linder: cheio de erro de sintaxe

int main(){
    array<array<char,3>,3> board{};
    char player = "X";
    cout << "Jogo da velha 3x3\nPlayers: X e O\n insira linha e coluna(1..3\n)";
    printBoard(board);
    while(true){
        int linha,coluna;
        cout << "Jogador" << player << "Informe linha e coluna:";
        if(!(cin >> linha >> coluna)) {
            cout << "Entrada Invalida. Encerrando\n";break;
        }
        if(linha < 1 || linha > 3 || linha < 1 || linha > 3){
            cout << "Posicao fora do intervalo. Tente novamente.\n";
            continue;
        }

        int r = linha - 1, c = coluna - 1
        if(board[r][c] != 0){
            cout << "Quadrado Ocupado. Escolha outra posicao.\n";
            continue;
        }

        board[r][c] = player;
        printBoard(board)

        if(checkWin(board,player)){
            cout << "Jogador" << player << "Venceu\n";
            break;

        }

        if(boardFull(board)){
            cout << "Empate! Tabuleiro cheio\n";
            break;
        }

        player = (player == "X")?"O":"X";
    }
    return 0;
}