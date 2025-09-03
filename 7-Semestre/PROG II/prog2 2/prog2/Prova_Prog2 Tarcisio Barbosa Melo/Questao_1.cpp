#include <iostream>
#include <format>

/* Escreva um programa que esBme o valor da constante matemáBca e usando 
a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use 
o tipo long para o cálculo do fatorial.
*/

unsigned long int Calcular_Fatorial(int numero);

//linder: apesar de parecer correto, está truncando e saindo 2 de resultado...

int main(){

    int Num_Termos;
    std::cout << "Determine o numero de termos da soma: ";
    std::cin >> Num_Termos;
    std::cout << std::endl;

    long int Constante_E {1};

    for(int i{1}; i < Num_Termos + 1; i++){

        Constante_E += 1 / Calcular_Fatorial(i);

    }
    std::cout << std::format("Constante e = {}", Constante_E);
    
    return 0;
}

unsigned long int Calcular_Fatorial(int numero){

    long int Fatorial{1};

    for(int i{1}; i < (numero + 1); i++){

        Fatorial *= i;

    }

    return Fatorial;
}