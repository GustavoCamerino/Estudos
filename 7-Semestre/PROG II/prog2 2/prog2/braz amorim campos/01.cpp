#include <iostream>

long int fatorial(int n);

int main(){
    int quantTermos {0};
    long double soma {1.0};
    long double proxFracao {0.0};

    std::cout << "Informe a quantidade de termos da soma: ";
    std::cin >> quantTermos;

    for(int i{1}; i <= quantTermos; i++){
        proxFracao = 1.0 / fatorial(i);
        soma += proxFracao;
    }

    std::cout << "e estimado: " << soma << std::endl;

    return 0;
}

long int fatorial(int n){
    if(n == 0){
        return 1;
    }
    return fatorial(n - 1) * n;
}