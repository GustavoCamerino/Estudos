#include <iostream>

int main(){
    float constE{1};
    int termos{0};

    std::cout << "Informe o número de termos da soma: " << std::endl;
    std::cin >> termos;

    //calculo do valor da constante 'e'
    for(int i{1}; i <= termos; i++){
        constE += 1/fatorial(i);
    }

    //linder: faltou somar 1 ao valor final
    std::cout << "Valor da constante: " << constE << std::endl;
    return 0;
}

long int fatorial(int valor){
    if (valor <= 1){
        return 1;
    } else {
        return valor * fatorial(valor - 1);
    }
}