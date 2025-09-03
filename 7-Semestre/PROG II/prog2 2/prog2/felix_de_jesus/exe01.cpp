//Felix de Jesus Sousa Barros 
//Questão 1

//1. (2.0 pts) Escreva um programa que estime o valor da constante matemática e usando
//a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use
//o tipo long para o cálculo do fatorial. e = 1+ 1/1! + 1/2! + 1/3! .....
 
#include <iostream>
#include <math>
  
//linder: nao esta fazendo nada do que eu pedi
 int main () {
   
    int numero;
    std::cout << "Digite um número inteiro:\n  ";
    std::cin >> numero;

    float fatorial = 1 + (1/(int numero)!) + (1/(int numero)!); //linder: sem sentido

    std::cout << "A soma da costante e com " << numero << "termos é igual a: "<< fatorial <<std::endl;

    return 0;

 }