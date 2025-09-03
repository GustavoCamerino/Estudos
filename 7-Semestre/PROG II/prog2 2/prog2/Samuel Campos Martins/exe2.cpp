(3.0 pts) Nesse exercício, você deve implementar o clássico jogo da velha 
bidimensional. Use um Array C++ 3x3 (matriz) para armazenar as jogadas. Cada jogador 
deve indicar suas jogadas inserindo um par de números inteiros representando os 
índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um 
'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado 
ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira 
uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém 
ganhou ou se houve empate. 

#include <iostrem>
#include <vector>

//linder: nao fez nada

int main(){
    int matriz;

    matriz = {{   |    |    |},
              {   |    |    |},
              {   |    |    |}};

    char x;
    char y;
    
}