#include <iostream>
//  (2.0 pts) Escreva um programa que esBme o valor da constante matemáBca e usando
//  a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use
//  o Bpo long para o cálculo do fatorial.

float constanteE(int numero){
    int numero = numero;
    float ecost{o}; //linder: errado 0 nao o

    if (numero > 1){
        for (int num = numero; num > 1; num--){
            ecost += (1 / fatorial(num - 1))
        }
        num = 0;
        ecost += 1;
        return ecost;
    }
    if else (numero = 1){ //linder: errado!
        return ecost = 1;
    }
    else{
        std::cout << "Numero invalido" << std::endl;
    }


}

//linder: errado!
int fatorial(int termo){
    int Fatorial{termo};

    if (termo = 1){
        return fatorial = 1; //linder: errado!
    }
    else
    {
        for (int i = termo; i > 1; i--){ //linder: errado!
            Fatorial = Fatorial * fatorial(termo - 1); 
                
        }
        return Fatorial;

    }
}

int main(){
    int valor; 
    std::cout << "Digite o numero de termos da constante";
    std::cin >> valor << std::endl;

    int resultado = constanteE(valor);

    std::cout << "A contante matematica é:\t" << resultado << std::endl;
}