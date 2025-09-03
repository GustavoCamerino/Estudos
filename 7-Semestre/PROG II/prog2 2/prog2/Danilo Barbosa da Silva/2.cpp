// Prova 1
// Danilo Barbosa da Silva
// Questão 2

#include <iostream>
#include <array>


// Prototipos das Funcoes
bool verifica_jogo(const std::array<std::array<char,3>,3> &mtz);
bool valida_jogada(const std::array<std::array<char,3>,3> &mtz, const int &i, const int &j);
bool testa_char(const std::array<std::array<char,3>,3> &mtz, char c);

int main () {
    // Declaracao do array bidimensional
    std::array<std::array<char,3>,3> mtz = {{{' ', ' ', ' '},
                                            {' ', ' ', ' '},
                                            {' ', ' ', ' '}}}; //linder: inicializacao errada

    bool flag{true};
    int vez{0};
    int i{0};
    int j{0};
    int resultado{0};

    // Jogador 1 = X
    // Jogador 2 = O

    while(flag) {
        vez++;
        std::cout << "Vez do Jogador: " << vez;
        
        std::cout << "Insira cordenada (i): " << std::endl;
        std::cin >> i;

        std::cout << "Insira cordenada (j): " << std::endl;
        std::cin >> j;

        if(valida_jogada(mtz,i,j)) {
            if(vez == 1) {
                mtz[i][j] = 'X';

            } else if (vez == 2) {
                mtz[i][j] = 'O';
            }
            // Alterna vez
            vez %= 2;
        } else {
            std::cout << "Jogada Invalida!!! (Tente Novamente)" << std::endl;
        }

        resultado = verifica_jogo(mtz);

        // Finaliza o jogo se empatar ou alguem ganhar
        if(resultado) {
            flag = false;
        }
    }

    return 0;
}

// Verifica se houve algum ganhador
bool verifica_jogo(const std::array<std::array<char,3>,3> &mtz) {
    bool x = testa_char('X'); //linder: falta parametro
    bool bolinha = testa_char('O'); //linder: falta parametro
    bool espacos_vazios = testa_char(' ');

    if(x) {
            std::cout << "Jogador 1 Ganhou !!!" << std::endl;
            return true;

        } else if(bolinha) {
            std::cout << "Jogador 2 Ganhou !!!" << std::endl;
            return true;

        } else if(espacos_vazios){
            return false;

        } else {
            std::cout << "Empate !!!" << std::endl;
            return true;
        }
    
}
//linder: nao funciona
bool testa_char(const std::array<std::array<char,3>,3> &mtz, char c) {
    
    // Verifica se ainda há espaços vazios
    int soma_ponto{0};
    if(c == ' ') {
        bool vazio{false};
        for(int i = 0; i < mtz.size(); i++) {
            for(int j = 0; j < mtz.size(); i++) {
                if(mtz[i][j] == ' ') {
                    bool vazio = true;
                }
            }
        }
    }

    // Horizontal
    for(int i = 0; i < mtz.size(); i++) {
        for(int j = 0; j < mtz.size(); i++) {
            if(mtz[i][j] == c) {
                soma_ponto++;
            }
        }
        if(soma_ponto == 3) {
            return true;
        } 
        soma_ponto = 0;
    }

    // Vertical
    for(int j = 0; j < mtz.size(); j++) {
        for(int i = 0; i < mtz.size(); i++) {
            if(mtz[i][j] == c) {
                soma_ponto++;
            }
        }
        if(soma_ponto == 3) {
            return true;
        } 
        soma_ponto = 0;
    }

    // Diagonal Principal
    for(int i = 0; i < mtz.size(); i++) {
        if(mtz[i][i] == c) {
            soma_ponto++;
        }
    }
        if(soma_ponto == 3) {
            return true;
        } 
        soma_ponto = 0;
    

    // Diagonal Secundaria
    j = 0;
    for(int i = mtz.size() - 1; i >= 0; i--) {
        if(mtz[i][j] == c) {
            soma_ponto++;
        }
        if(soma_ponto == 3) {
            return true;
        }
        j++; 
        soma_ponto = 0;
    }
}


bool valida_jogada(const std::array<std::array<char,3>,3> &mtz, const int &i, const int &j) {
    if(mtz[i][j] == ' ') {
        return true;
    } else {
        return false;
    }
}

/*2. (3.0 pts) Nesse exercício, você deve implementar o clássico jogo da velha
bidimensional. Use um Array C++ 3x3 (matriz) para armazenar as jogadas. Cada jogador
deve indicar suas jogadas inserindo um par de números inteiros representando os
índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um
'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado
ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira
uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém
ganhou ou se houve empate.*/