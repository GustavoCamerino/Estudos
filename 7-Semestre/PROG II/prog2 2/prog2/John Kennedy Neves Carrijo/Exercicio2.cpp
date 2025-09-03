#include <iostream>
#include <format>
#include <array>
#define T 3

//linder: parametro definido errado
int jogo_velha(std :: array<std :: array<char,T>>&jogo){
    int jogador1{0}
    int jogador2{0};
    for(int i{0};i<jogo.size();i++){
        for(int j{0};j<jogo.size()-1;j++){//linder: numeros??
            if((numeros.at(i)=='X' && numeros.at(j)=='X') || (numeros.at(i)=='O' && numeros.at(j)=='O')){
                std :: cout <<"Posição ocupada tente de novo"<< std :: endl;
                return -1;
            }else if((numeros.at(i)=='X' || numeros.at(j)=='X')  && (numeros.at(i+1)=='X' || numeros.at(j+1) =='X') && (numeros.at(i+2) || numeros.at(j+2)=='X') ){
                jogador1=1;// 1-> Vitoria , 0 ->  Derrota , 2 -> empate
                jagador2=0;
            }else if((numeros.at(i)=='O' || numeros.at(j)=='O')  && (numeros.at(i+1)=='O' || numeros.at(j+1) =='O') && (numeros.at(i+2) || numeros.at(j+2)=='O') ){
                jogador2=1
                jagador1=0;
            }else{
                jogador1=2;
                jagador2=2;
            }
        }
    }

    if(jogador1==1){
        return 1;//se o jogador1 vencer ele vai retorna 1
    }else if(jogador2==1){
        return 2; // se o jogadro2 vencer ele vai retorna 2
    }else{
        return 3;//se houver empate retorna 3
    }

}

int main(){
    std :: array<std :: array<char>,T> numeros;
    char escolha;
    int vencedor{0};
    int linha{0},coluna{0};
    do{
        std :: cout <<"Escolha X ou O digite em Maiusculo";
        std :: cin >> escolha;

        std :: cout <<"Digite a linha:";
        std :: cin >> linha;

        std :: cout << "Digite a coluna:";
        std :: cin >>coluna;

        for(int i{0};i<T;i++){
            for(int j{0};j<T-1;j++){
                if(i==linha && j==coluna){
                    numeros.at(i)=escolha;
                }
            }
        }

        vencedor=jogo_velha(numeros);



    }while(vecendor!=1 && vecendor !=2 && vecendor !=3);

    return 0;
}