#include <iostream>
#include <random>
#include <format>

//variavel global para o numero secreto
int gera_num();
int tentativa(int chute);

int num_sec = gera_num() ;
int main(){
    int chute ;
    do{ 
        std::cout << "Digite um valor para chute : \n";
        std::cin >> chute ;

        int tent = tentativa(chute) ;
    }while(tent != 0 ); //linder: tent tá fora de escopo

    return 0 ;
}

//funcao para gerar numero aleatorio 
int gera_num(){
    static std::random_device seed ; 
    static std::default_random_engine engine{seed} ;
    static std::uniform_int_distribution generator{1, 100} ;

    int num = generator(engine) ;
    return num ;
}

int tentativa(int chute){
    //inicializando variavel estatica 
    static int qnt_chutes{0} ;
    qnt_chutes++ ;

    if(chute == num_sec){
        std::cout << std::format("Acertou!!\nQuantidade de chutes {}.".qnt_chutes);
        return 0 ;
    }

    else if(chute > num_sec){
        std::cout << "Errou!! chute muito alto !\n" ;
        return 1 ;
    }else{
        std::cout <<  "Errou!! chute muito baixo !\n" ;
        return -1 ;
    }
}
