#include <iostream>
#include <format>
#include <random>

int numero_sorteado{0};
static int contador_de_chutes{0}; //linder: nao faz sentido definir aqui static

int sorteia(){

    static std :: random_device seed;
    static std :: default_random_engine gerador{seed ()};
    static std :: uniform_int_distribution gerador{1,100}; //linder: mesmo nome!

    numero_sorteado=gerador(engine);

    return numero_sorteado;
}

int chute(int n){
    numero_sorteado=sorteia();
    contador_de_chutes++;
    if(n==numero_sorteado){
        std :: cout <<"Você acertou" << std :: endl;
        return 0;
    }else{
        if(n>numero_sorteado){
            std :: cout <<"Errou tente novamente. Muito alto" << std :: endl;
            return 1;
        }else if(n<numero_sorteado){
            std :: cout <<"Errou tente novamente. Muito baixo" << std :: endl;
            return -1;
        }
    }
}

int main(){
    int resultado{-2};
    int palpite{0};
    do{
        std :: cout <<"Digite um palpite:";
        std :: cin >> palpite;

        resultado=chute(palpite);
        if(resultado == 0){
            std :: cout << std :: format("Numero de chutes total:{}\n",contador_de_chutes);
        }
    }while(resultado!=0);

    return 0;
}