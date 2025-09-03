#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // para uso do sort
// Prova 1
// Programação 2
// 13/08/2025
// Aluno:João Paulo Alves Campos
// (2.5 pts) Use um vector para armazenar uma lista de valores numéricos fornecidos pelo
// usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular
// a média dos valores, uma para calcular a mediana dos valores (valor central após
// ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se,
// vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível.
// Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos
// eles são considerados e, portanto, sua função deve retornar um vector com esses
// valores. Escreva o programa principal de teste.

//linder: ok
float media(const std::vector<int> &lista){
    float media{0};
    for(int i=0; i<lista.size(); i++){
        media+=lista.at(i);
    }
    return media/lista.size();
}

//linder: errado!
int mediana(std::vector<int> &lista){
    std::vector<int> copia = lista;
    //linder: errado uso do metodo sort
    copia.sort(std::begin(copia),std::end(copia)); //ordena o vector porem nao lembro se era std::sort(inicio<vector>, fim<vector>) ou <vector>.sort(inicio<vector>, fim<vector>)
    
    int mediana = copia.at((copia.size()-)1/2); //linder: erro!
    if((copia.size()-1)% 2 !=0){
        return (mediana + copia.at(copia.size()/2))/2;
    } 
    else{
        return mediana;
    }
}

//linder: nao funciona!
std::vector<int> moda(std::vector &lista){
    std::vector<int>unicos{lista.at(0)};
    bool achou = false;
    for(int i= 0; i<lista.size();i++){
        for(int j=0;j<unicos.size();j++){
            if(lista.at(i)==unicos.at(j)){
                achou= true;
            }
        }
        if(achou==false){
            unicos.push_back(lista[i]);
        }
    }

    //bloco acima adiciona os elementos unicos a um vector, para poder encontrar a moda;
    int moda = lista.at(0);
    int moda_contagem{0};
    int moda_maior = moda_contagem;

    for(int i=0;i<unicos.size();i++){
        for(int j=0; j<lista.size();j++){
            if(unicos[i]==lista[j]){
                moda_contagem++;
                if(moda_contagem > moda_maior){
                    moda = unicos[i];
                }
            }
        }
        moda_contagem =0;
    }
    return moda;
}

//terminar depois para entregue uma bimodal
//atualizaçao nao deu tempo :( 

//linder: sem programa principal para teste!