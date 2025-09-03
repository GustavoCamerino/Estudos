#include <iostream>
#include <array>

using namespace std;

int main() {

    array<array<char, 3> linha, 3> coluna, mtx; //linder: definicao errada

    int linhas, colunas;
    char op;
    char flag;

    for(int i = 0; i < mtx.size(); i++) {
        for(int j = 0; j < mtx.size(); j++) {
            mtx.at(i).at(j) = '0';
        }
    }
    
    //linder: nao funciona
    do
    {
        cout << "Informe a linha e a coluna que deseja inserir um X ou O.";
        cin >> linhas;
        cin >> colunas;

        cout << "Informe o que deseja colocar: X ou O";
        cin >> op;
        for(int i = 0; i < mtx.size(); i++) {
            for(int j = 0; j < mtx.size(); j++) {
                if(mtx.at(linhas).at(colunas) != '0'){
                    cout << format("escolha {} adicionada a posicao {},{}", op, linha, coluna);
                    mtx.at(i).at(coluna) = op;

                    for(int k = 0; k < mtx.size(); k++) {
                        for(int l = 0; l < mtx.size(); l++) {
                            if(mt)
                        }
                    }

                }else {
                    cout << "Opção inválida, já existe elementos nela.";
                    }
                }   
            }
            } while (flag != 1);
}