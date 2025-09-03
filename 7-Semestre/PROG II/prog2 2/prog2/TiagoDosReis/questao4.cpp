#include <iostream>
#include <random>

//linder: nao funciona
using namespace std;

int tentativa_jogador;

int sorteio(int numero_secreto) {

    numero_secreto = random(int<1,100>);
    return numero_secreto;

}

int tentativa (int chute) {

    tentativa_jogador = tentativa;

    if(tentativa == numero_secreto) {

        cout << "Você acertou o numero secreto" << endl;
        return 0;
 
    } else if (tentativa > numero_secreto){

        cout << "Você chutou muito alto. Tente novamente." << endl;
        return 1;

    } else {

        cout << "Você chutou baixo. Tente novamente." << endl;
        return -1;

    }

    return tentativa;

}

int main() {

int quantas_vezes_chamada;

sorteio();
cout << "Jogo de adivinhação" << endl;

while (numero_secreto != tentativa_jogador) {

cout << "Digite o valor que você acha que é: " << endl;

cin >> tentativa_jogador;
tentativa(tentativa_jogador);

}

return 0;

}