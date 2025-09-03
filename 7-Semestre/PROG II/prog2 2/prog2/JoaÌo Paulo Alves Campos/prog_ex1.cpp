#include <iostream>

// Prova 1
// Programação 2
// 13/08/2025
// Aluno:João Paulo Alves Campos
// 1. (2.0 pts) Escreva um programa que esBme o valor da constante matemáBca e usando
// a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use
// o Bpo long para o cálculo do fatorial.
// 𝑒 = 1 + 1
// 1! + 1
// 2! + 1
// 3! + ⋯

//linder: implementacao errada!
long fatorial(int num){
    while(true){
        if(num == 0){
            break; //linder: errado (return 1)
        }
        else{
            return num * fatorial(num-1);
        }
    }
}
//linder: retorno deveria ser float e nao long
long Euler(int num){
    float resultado{0};
    for(int i=1; i<=num;i++){
       resultado+= 1/fatorial(i);
    }
    return 1+resultado;
}
int main(){
    int num{0};
    std::cout << "Digite a entrada para calcular o EULER :" << std::endl;
    std::cin >> num;
    std::cout << "Portanto o resultado é : " << Euler(num) << std::endl;
    return 0;
}