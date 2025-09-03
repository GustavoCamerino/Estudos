#include <iostream>
#include <format>


using namespace std;

long double fatorial(double num);

//linder: errado, sem lógica nenhuma
long double fatorial(double num) {

    for(int termo = num; termo >= 1; termo--){
        double fatorial *= termo;
    }

    return fatorial;
}

int main() {

    int n_termo {0};
    double e;  //linder: sem inicializacao

    cout << "Informe qual o termo que voce deseja calcular da sequencia. " << endl;
    cin >> n_termo;

    for(int i = 0; i <= n_termo; i++) {

        e += 1/fatorial(i);
    }

    cout << format("O resultado da sequencia eh {}.", e);

    return 0;
}

