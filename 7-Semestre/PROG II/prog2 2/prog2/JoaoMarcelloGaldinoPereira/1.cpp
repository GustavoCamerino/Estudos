#include <iostream>
#include <cmath>

// Prototipacao
long int Fatorial(int n);


int main()
{
    // Variaveis para receber o valor total, denominador e termo de cada soma
    int number {0};
    double valore {0.0};
    double termo {0.0};

    // Recebendo ate que denominador o usuario quer 
    std::cout << "Insira o denominador: ";
    std::cin >> number;

    // Laco para somar o valor de e
    for(int i {0} ; i <= number ; i++){
        termo = 1/Fatorial(i);
        valore += termo;
    }

    // Imprimindo o valor da constante
    std::cout << "\nO valor da constante matematica \'e\' = " << valore;

    return 0;
}

// Definicao
long int Fatorial(int n)
{   
    // Caso base da recursao
    if(n == 0){
        return 1;
    } 
    // Caso base da recursao
    if else (n == 1){ //linder: errado!
        return 1;
    } 
    else {
        return n * Fatorial(n-1); // Calcula o fatorial recursivamente
    }
}