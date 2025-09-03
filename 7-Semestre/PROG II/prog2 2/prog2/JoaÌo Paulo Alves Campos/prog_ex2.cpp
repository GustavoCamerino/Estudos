#include <iostream>

// Prova 1
// Programação 2
// 13/08/2025
// Aluno:João Paulo Alves Campos
// (3.0 pts) Nesse exercício, você deve implementar o clássico jogo da velha
// bidimensional. Use um Array C++ 3x3 (matriz) para armazenar as jogadas. Cada jogador
// deve indicar suas jogadas inserindo um par de números inteiros representando os
// índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um
// 'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado
// ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira
// uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém
// ganhou ou se houve empate.

//linder: sem lógica nenhuma, o parametro eh inteiro
bool tem_espaco(int &array){
    bool espaco = false;
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            if(array[i][j]==0){
                espaco = true;
            }
        }
    }
    return espaco;

}
bool ganhou(int &array, int jogador){
    bool ponto = false
    if((array[0][0]==jogador) &&(array[1][0]==jogador) && (array[2][0]==jogador)){ //linha 0 ate a coluna 0-3
        return ponto =true;
        }
    if((array[1][0]==jogador) &&(array[1][1]==jogador) && (array[1][2]==jogador)){
        return ponto = true;
        }
    if((array[2][0]==jogador) &&(array[2][1]==jogador) && (array[2][2]==jogador)){
        return ponto = true;
    }
    //acima a verificaçao por linhas

    if((array[0][0]==jogador)&&(array[1][0]==jogador)&&(array[2][0]==jogador)){
        return ponto = true;
    }
    if((array[0][1]==jogador)&&(array[1][1]==jogador)&&(array[2][1]==jogador)){
        return ponto = true;
    }
    if((array[0][2]==jogador)&&(array[1][2]==jogador)&&(array[2][2]==jogador)){
        return ponto = true;
    }
    //acima a verificaçao por colunas

    if((array[0][0]==jogador)&&(array[1][1]==jogador)&&(array[2][2]==jogador)){
        return ponto = true;
    }
    
    if((array[0][2]==jogador)&&(array[1][1]==jogador)&&(array[2][0]==jogador)){
        return ponto = true;
    }
    //acima a verificaçao se ganhou ou nao
    else{
        return ponto;
    }

}




int jogo_da_velha(int entrada1, int entrada2, int jogador){
    int array[[0,0,0],[0,0,0],[0,0,0]]; //linder: nao pedi array C
    if(tem_espaco(array)){
        for(int i =0;i<=entrada1;i++){
            for(int j =0;j<=entrada2;j++){
                if(array[i][j] != 0){
                    std::cout << "Local invalido!"   
                }
                else{
                    if(jogador == 1){
                        array[i][j]= 1;
                        if(ganhou(array,1)== true){
                            std::cout << "Parabens jogador 1, você ganhou!"
                            return 1;
                        }
                    }
                    if(jogador == 2){
                        array[i][j]= 2;
                        if(ganhou(array, 2)==true){
                            std::cout << "Parabens jogador 2, você ganhou!"
                            return 2;
                        }
                    }
                }
            }
        }
    }
    else{
        std::cout << "Deu velha..." << std::endl;
    }
}


int main(){
    int entrada1, entrada2;
    std::cout << "Começa o jogo da velha, passe as cordenadas sendo elas\n[linha][coluna]" <<std::endl;
    while(true){
        std::cout<<"jogador 1: " <<std::endl;
        std::cin >> entrada1 >> entrada2;
        if(jogo_da_velha(entrada1, entrada2, 1)==1){
            break;
        }
        std::cout<<"jogador 2: " <<std::endl;
        std::cin >> entrada1 >> entrada2;
        if(jogo_da_velha(entrada1, entrada2, 2)== 2){
            break;
        }
    } // provavelmente esta errado, e nao consigo achar erro...s
    std::cout << "Obrigado por jogar!" << std::endl;
}