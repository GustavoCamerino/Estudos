/*
Escreva um programa que esme o valor da constante matemá ca e usando 
a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use 
o po long para o cálculo do fatorial. 
*/

double fatorial(int);

#include <iostream>

int main(){

    int n;
    std::cout << "digite o numero de termo " << std::endl;
    std::cin >> n;

    double e{1.0};
    if (n == 1) {
        std::cout << "o termo de " << n << " e = " << e << std::endl;
    }
    else{
        for (size_t i = 1;i < n;i++){
            e += (1/fatorial(i));
        }
        std::cout << "o termo de " << n << " e = " << e << std::endl;
    }
    return 0;
}

double fatorial(int n){
    double soma_fac{1};
    for (size_t i = 1;i <= n;i++){
        soma_fac = soma_fac * i;
    }
    return soma_fac;
}



