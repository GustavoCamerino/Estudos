/**
 * @author Vitória Calonga dos Santos
 * @brief Escreva um programa que esme o valor da constante matemá ca e usando 
    a fórmula abaixo. O número de termos da soma deve ser fornecido pelo usuário. Use 
    o po long para o cálculo do fatorial. 
*/
#include <iostream>

long factorial(int n);
long termo(int n);

int main(){
    int n{0};

    std::cout << "Informe o valor de n: ";
    std::cin >> n;

    std::cout << "e = " << termo(n) << endl; //erro std::endl

    return 0;
}

long factorial(int n){
    long fatorial {n}; // erro! fatorial deveria comecar com 1 e vc está usando o mesmo
                       // nome da funcao para a variavel
    for(int i{n}; i >= 1 ; --i){
        fatorial *= i;
    } 
    long fatorial;
}

long termo(int n){
    long e{1};
    for(int i{1}; i <= n; i++){
        e += ( 1 /factorial(i));
    }

    long fatorial; // Erro!! sua funcao nao faz retorno, deveria retornar e
}