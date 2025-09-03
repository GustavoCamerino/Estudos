#include <iostream>
#include <format>
#include <algorithm>
#include <vector>

//PROTOTIPOS    AS FUNCOES CONSIDERAM QUE OS ARRAYS 
template<typename T>
double calcula_media(const std::vector<T> &lista);

template<typename T>
T calcula_mediana(std::vector<T> &lista);

template<typename T>
T calcula_moda(std::vector<T> &lista);

int main(){

    //testes 1
    std::vector<int> vec (7) {1,5,5,4,3,2,7} ; //linder: inicializando errado
    double media = calcula_media(vec) ;
    int mediana = calcula_mediana(vec) ;
    int moda = calcula_moda(vec) ;

    std::cout << std::format("media = {} \nmediana = {}\nmoda = {}\n",media,mediana,moda) ;
    // saida esperada media = aproximadamente 4 ; mediana 4 ; moda = 5


    
    //testes 2
    std::vector<int> vec(7) {1,6,5,4,3,2,7} ; 
    double media = calcula_media(vec) ;
    int mediana = calcula_mediana(vec) ;
    auto moda = calcula_moda(vec) ;

    std::cout << std::format("media = {} \nmediana = {}\nmoda = {}\n",media,mediana,moda) ;
    // saida esperada media = 4 ; mediana 4 ; moda = vetor com todos os elementos

}


template<typename T>
double calcula_media(const std::vector<T> &lista){
    T sum{0} ;
    for(const T num : lista){
        sum += num ;
    }

    double media = sum/lista.size() ;
    return (media)
}


template<typename T>
T calcula_mediana(std::vector<T> &lista){
    T mediana ;
    T aux ;
    std::sort(std::begin(lista),std::end(lista)) ;
    aux = lista.size()/2 ;
    
    if((lista.size()%2) == 0){
        mediana = (lista.at(aux) + lista.at(aux+1))/2 ; //linder: errado
    }
    else{
        mediana = lista.at(aux) ;
    }

    return mediana ;
}

//linder:nao funiciona
template<typename T>
T calcula_moda(std::vector<T> &lista,&freq){ //linder: freq nem tem tipo declarado

    if(lista.empty()){
        return lista ;
    }

    std::sort(std::begin(lista),std::end(lista));
    
    //variaveis auxiliares
    T num_atual = lista.at(0);
    int conta_atual{1} ;
    T moda {num_atual} ;
    int conta_moda{1} ;
    for(int i{1} ; i < lista.size() ; i++){
        if(lista.at(i) == num_atual){
            conta_atual++;
        }
        else{
            if(conta_atual > conta_moda){
                moda = num_atual ;
                conta_moda = conta_atual ;
            }
            num_atual = lista.at(i);
            conta_atual = 1 ;
        }

    if(conta_atual > conta_moda){
        moda = num_atual ;
    }

    if(conta_moda == 1){
        return lista ;
    }    

    return moda ;
    }
}
