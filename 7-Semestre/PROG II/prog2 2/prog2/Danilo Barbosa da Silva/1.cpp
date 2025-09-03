// Prova 1
// Danilo Barbosa da Silva
// Questão 1

#include <iostream>

// Prototipo
int fatorial(int n);

int main () {
    long e{1};
    int interador{0};

    //linder: aproximacao (com x)
    std::cout << "Informe a quantidade de termos para aprocimação: " << std::endl;
    std::cin >> interador;

    for(int n = 1; n <= interador; n++) {
        e += 1/(fatorial(n)); //linder: divisao inteira causa truncamento
    }

    std::cout << "e = " << e << std::endl;

    return 0;
}

// Calcula fatorial
int fatorial(int n) { //linder: pedi para definir com retorno long
    if(n == 0) {
        return 1 //linder: falta ;
    } else {
        n * fatorial(n-1); //linder: deveria retornar esse valor
    }
}


/* (2.0 pts) Escreva um programa que esBme o valor da constante matemáBca e usando
a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use
o Bpo long para o cálculo do fatorial.*/
