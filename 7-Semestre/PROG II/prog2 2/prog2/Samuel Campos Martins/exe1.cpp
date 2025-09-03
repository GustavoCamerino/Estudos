(2.0 pts) Escreva um programa que esme o valor da constante matemá ca e usando 
a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use 
o po long para o cálculo do fatorial. 

� =1+ 1/ 1!+ 1/2!+ 1/ 3! + ....

#include <iostream>

using namespace std;

//linder: errado!
int fatorial(){
    long e = 1;
    long n; //linder: indefinido!
    for(long i = n; i < e; --i){
        n * (i - 1) + (n - 1);
    }
}

int main(){
    long n;
    cout << "Digite o valor: ";
    cin >> n;

    long resultado;
    resultado = fatorial(n);
    return 0;
}