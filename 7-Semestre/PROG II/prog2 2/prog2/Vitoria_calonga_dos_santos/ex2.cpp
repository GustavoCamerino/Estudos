/**
 * @author Vitoria Calonga dos Santos
 * @brief Nesse exercício, você deve implementar o clássico jogo da velha 
    bidimensional. Use um Array C++ 3x3 (matriz) para armazenar as jogadas. Cada jogador 
    deve indicar suas jogadas inserindo um par de números inteiros representando os 
    índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um 
    'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado 
    ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira 
    uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém 
    ganhou ou se houve empate. 
*/
#include <iostream>
#include <array>

int main(){
    // linder: erro! nao sabe definir matriz c++. 
    std::array<std::array<std::array<char, 3>char, 3>, char, 3 > mtx{{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
    int i{0}, j{0}, interacao;
    char ch{' '};
    
    bool flag = true;
    bool flag2 = false;
    bool flag3 = true;
    while(flag && (interacao > 9)){
        //com 9 interacoes a matriz fica cheia e da velha se niguem ganhou 
        interacao++;

        std::cout << "Entre com um X ou O: ";
        std::cin >> ch;
        std::cout << "Entre com as coordenadas: ";
        std::cin >> i >> j;

        //linder: Erro! mtx nem foi definido
        if(mtx[i][j] != ' '){
            std::cout << "Espaco ocupado. Entre com novas coordenadas: ";

            flag2 = true;
            while(flag2){
                std::cin >> i >> j;

                if(mtx[i][j] != ' '){
                    std::cout << "Espaco ocupado. Entre com novas coordenadas: ";
                }else{
                    flag2 = false;
                }
            }
        }

        mtx[i][j] = ch;
        
        //linder: sua logica de verificacao nao funciona!

        //verifica linha 
        int verifica{0};
        for(int i{0}; i < 3; i++){ 
            if(verifica == 2){
                std::cout << mtx[i-1][i-1] << "Ganhou!"<< std::endl;
                flag = false;
            }else{
                verifica = 0;
            }
            for(int j{0}; j < 2;j++){ //menor que 2 para que nao acabe procurando um valor que nao existe ps:nao lembro a sintase do at() em array bidi
                if(mtx[i][j] == mtx[i][j+1]){
                    verifica++;
                }
            }
        }
        if(verifica == 2){
            std::cout << mtx[3][3] << "Ganhou!"<< std::endl;
            flag = false;
        }

        //verifica coluna
        verifica = 0;
        for(int j{0}; j < 3; i++){ 
            if(verifica == 2){
                std::cout << mtx[i-1][i-1] << "Ganhou!"<< std::endl;
                flag = false;
            }else{
                verifica = 0;
            }

            for(int i{0}; i < 2;j++){ //menor que 2 para que nao acabe procurando um valor que nao existe ps:nao lembro a sintase do at() em array bidi
                if(mtx[i][j] == mtx[i+1][j]){
                    verifica++;
                }
            }
        }
        if(verifica == 2){
            std::cout << mtx[3][3] << "Ganhou!"<< std::endl;
            flag = false;
        }

        //verifica diagonais
        verifica = 0;
        for(int i{0}; i < 2; i++){ 
            if(mtx[i][i] == mtx[i + 1][i + 1]){
                verifica++;
            }
        }
        if(verifica == 2){
            std::cout << mtx[1][1] << "Ganhou!"<< std::endl;
            flag = false;
        }

        verifica = 0;
        for(int i{3}; i > 0; i--){ 
            if(mtx[i][i] == mtx[i + 1][i + 1]){
                verifica++;
            }
        }
        if(verifica == 2){
            std::cout << mtx[3][3] << "Ganhou!"<< std::endl;
            flag = false;
        }
    
    return 0;
}
}