/*
Use um vector para armazenar uma lista de valores numéricos fornecidos pelo 
usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular 
a média dos valores, uma para calcular a mediana dos valores (valor central após 
ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se, 
vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível. 
Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos 
eles são considerados e, portanto, sua função deve retornar um vector com esses 
valores. Escreva o programa principal de teste. 
*/

int moda(std::vector&);
double media(std::vector&,int);
double mediana(std::vector&,int);

#include <iostream>
#include <vector>
#include <iteretor>

int main(){
    int cont{0};
    int entrada;

    std::vector numeros; //vector é template
    std::cout << "digite os valores (digite -1 para parar)" << std::endl;
    std::cin >> entrada;

    while(entrada != -1){ //linder: entrada pode ser negativa...
        numeros.push_back(entrada);
        cont++;
    }
    numeros.sort(std::begin(0), std::end(cont));

    std::cout << "moda = " << moda(numeros) << std::endl;
    std::cout << "media = " << media(numeros,cont) << std::endl;
    std::cout << "mediana = " << mediana(numeros,cont) << std::endl;
    return 0;
}

double mediana(std::vector& numeros,int cont){
    if(cont%2 == 0){
        return static_cast<double> (numeros.at((cont/2.0)) + numeros.at((cont/2.0)-1)) / 2.0;
    }else{
        return static_cast<double> numeros.at((cont/2.0)) / 2.0;
    }
}

double media(std::vector& numeros,int cont){
    double soma{0};
    for (size_t i = 0;i < numeros.size();i++){
        soma += numeros.at(i);
    }
    return static_cast<double> (soma/cont); //linder: vector carrega o tamanho
}

//linder: nao funciona
int moda(std::vector& numeros){
    int frequencia;
    int frequencia_moda{0};
    int moda{0};
    for (size_t i = 0;i < numeros.size();i++){
        frequencia = 0;
        for (size_t j = i;j < numeros.size();j++){
            if (numeros.at(i) == numeros.at(j)) frequencia++;
        }
        if (frequencia > frequencia_moda){
            moda = numeros.at(i);
            frequencia_moda = frequencia;
        }
    }
    return moda;
}

