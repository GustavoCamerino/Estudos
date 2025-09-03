#include <iostream>

//protótipo das funções
long int fatorial(int);
double euler(int);


int main() {

    int x{0};
    double resultado{0.0};

    std::cout << "Insira o numero da soma da constante matematica: " << std::endl;

    std::cin >> x;

    resultado = euler(x);
    std::cout << "O valor da soma da constante é: " << resultado << std::endl;

    return 0;
}

//função fatorial recursiva
long int fatorial(int x) {

    if (x==0) return 1;

    return x * fatorial(x-1); 

}

//função para calcular 'e' iterativa
double euler(int x) {

    double euler{0.0};

    for (int i{0}; i <= x; i++) {
        euler += 1.0/fatorial(i);
    }
    return double; //linder: deveria ser return euler
}