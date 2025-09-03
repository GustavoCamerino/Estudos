#include <iostream>
#include <format>

/* Escreva um programa que estime o valor da constante matemática e usando 
a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use 
o tipo long para o cálculo do fatorial.*/

long float fatorial(int numero); //linder: nao existe long float

int main() {

    // Usuario informa o numero de termos
    int numero_termos;
    std::cout << std::format("Informe o numero de termos: ");
    std::cin >> numero_termos;

    long float e = 1.0; //linder: nao existe long float

    for (float i{1.0}; i <= numero_termos; i++) { //linder: incremento so pode com inteiro

        float termo = 1.0 / (fatorial(i));
        e += termo;
    }

    std::cout << std::format("e^{} = {:.5f}\n",numero_termos,e);

    return 0;
}

// Função que calcula o fatorial de um numero recursivamente
long float fatorial(int numero) { //linder: nao existe long float

    if (numero == 0) {
        return 1;
    }

    if (numero == 1) {
        return 1;
    }

    else {
        numero * fatorial(numero - 1); //linder: sem retorno
    }
}
