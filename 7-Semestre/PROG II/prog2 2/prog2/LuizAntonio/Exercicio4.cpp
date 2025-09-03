/*
UFMT - Bacharelado em Ciencia da Computação
Programação de Computadores II
Luiz Antonio Marquetti Girardi Junior 
*/


//linder: nao fez o que foi pedido
#include <random>
#include <string>
#include <iostream>


int GeraNumeroAleatorio(){
    static std::random.device; //linder: sintaxe errada
    static std::default_engine engine{seed()};
    static std::int_distribution GeraNumeroAleatorio(1,100);

    int numero_sorteado = GeraNumeroAleatorio();


}
int tentativa(int tentativa){
    std::cout <<"Informe um número para começar o jogo de advinhação" << std::endl;
    std::cin>>tentativa;

    

}


int main(){
    while (numero_sorteado != tentativa){
    if (numero_sorteado == tentativa){
        std::cout<<"Parabens!\n VOCÊ ACERTOU !" std::endl;
        }
    }
    // 



}