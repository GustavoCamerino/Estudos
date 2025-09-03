#include <iostream>
#include <vector> 

using namespace std;

//linder: nesse ponto do curso nem havia ensinado classe.
//linder: nao pedi para definir classe.
//linder: não fez como foi solicitado.
//linder: apresenta erro de logica.

class jogo_da_velha {
private: 
    vector<vector<char>> tabuleiro; //linder: pedi para armazenar em array
    char jogador_atual;             // nao vector

public:
    jogo_da_velha() {
        tabuleiro = vector<vector<char>>(3, vector<char>(3, ' '));
        jogador_atual = 'X';
    }
    void mostrar_tabuleiro() {
        cout << "\nTabuleiro: \n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << tabuleiro[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout<< "---------\n";
        }
    }
    bool posicao_valida(int linha, int coluna) {
        return linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' ';
    }
    bool verificar_vitoria() {
        for (int i = 0; i < 3; ++i) {
            if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') {
                return true;
            }
            if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ') {
                return true;
            }
        }
        if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ') {
            return true;
        }
        return false;
    }
    bool verificar_empate() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (tabuleiro[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
    void fazer_jogada() {
        int linha, coluna;
        bool jogada_valida = false;

        while (!jogada_valida) {
            cout << "Jogador " << jogador_atual << ", insira a linha e a coluna (0-2): ";
            cin >> linha >> coluna;

            if (posicao_valida(linha, coluna)) {
                tabuleiro[linha][coluna] = jogador_atual;
                jogada_valida = true;
            } else {
                cout << "Posicao invalida! Tente novamente.\n";
            }
        }
    }
    void alternar_jogador() {
        if (jogador_atual == 'X') {
            jogador_atual = 'O';
        } else {
            jogador_atual = 'X';
        }
    }
    void iniciar_jogo() {
        int rodadas = 0;

        while (true) {
            mostrar_tabuleiro();
            fazer_jogada();
            rodadas++;

            if (verificar_vitoria()) {
                mostrar_tabuleiro();
                cout << "Jogador " << jogador_atual << " Venceu!\n";
                break;
            }
            if (verificar_empate()) {
                mostrar_tabuleiro();
                cout << " Empate!\n";
                break;
            }
            alternar_jogador();
        }
    }
};

int main() {
    jogo_da_velha jogo;
    jogo.iniciar_jogo(); 
    return 0;
}

