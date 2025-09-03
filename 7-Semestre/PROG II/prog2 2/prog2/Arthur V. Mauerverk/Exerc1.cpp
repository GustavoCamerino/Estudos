#include <iostream>
#include <format>

using namespace std;

/*

Escreva um programa que estime o valor da constante matemática 'e' usando 
a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use 
o tipo long para o cálculo do fatorial. 
e = 1 + 1 / 1! + 1 / 2! + 1 / 3! + ⋯

*/ 

long int fatorial(int n_termos);

int main(){

    int n_termos;

    cout << "Digite a quantidade de termos: ";
    cin >> n_termos;

    double e = 1.0;
    double soma = 0.0;

    for (i = 1; i <= n_termos; i++){ //linder: nao definiu o tipo de i
                                     //linder: inicializou no estilo c
        soma += 1/fatorial(i);       //linder: divisao inteira

    }

    e += soma;

    cout << format("constante e = {}", e);

    return 0;
}

long int fatorial(int n_termos){

    if (n_termos == 1){
        return 1;
    }else{
        return n_termos * fatorial(n_termos - 1);
    }

}