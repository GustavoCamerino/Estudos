#include <iostream>
#include <random>
using namespace std;

//muitos erros!

int main() {
    random_engine (seed); //linder: nao existe
    default_random_distribution(seed()); //linder: nao existe
    uniform_int_distribution<int>  dist(1,100);

    char jogar = 's';
    cout << "gostaria de jogar novamente (s/n): "<<
    cin >> jogar;

    while (char jogar ='s' || char jogar = 'S'){
    int secreta = gen(seed); // linder: gen nao foi definido 
    int chute;
    int tentativas = 0;
    
    //linder: nao usou variavel estatica
        do {
            if(secreta < chute){
            cout << "1" << endl;
            tentativas++;
        }else if (secreta > chute){
            cout << "-1" << endl;
            tentativas++;
        }else {
            cout << "0, voce fez "<< tentativas << endl;
        }
        }while (chute != secreto){
            cout << "adivinhe o numero secreto: " << endl;
            cin >> chute;
        }
    }
    cout << "ate logo!"<< endl;
    return 0;

}