#include <iostream>
#include <random>

int random(int, int);
int tentativa(int);

int num_secreto;

//linder: errado
int random(int min, int max){
    static random_divece rd; //linder: sintaxe errada
    static mt19937 gen(rd());  //nunca foi sequer discutido mt19937
    using_int_distribution dist(min, max); //errado

    num_secreto = gen(dist());

    return 1;
}

//ok: funciona
int tentativa(int chute) {

    static int tentativa; //ok!

    if(chute == num_secreto) {
        tentativa++;
        return 0;
    }else if(chute > num_secreto) {
        tentativa++;
        return 1;
    }else if(chute < num_secreto) {
        tentativa++;
        return -1;
    }
}

int main () {

    const int min{1};
    const int max{100};
    int chute;
    int flag {0};

    do {
        cout << "Informe o chute da adivinhação: ";
        cin >> chute;
        flag = tentativa(chute);

        if(flag == 0) {
            cout << format(" Parabéns, voce acertou o numero {} usando {} tentativas", num_secreto, tentativa);
            flag = 2;
        }else if(flag == 1) {
            cout << "Errado, o número informado é maior que o número secreto.";
        }else if(flag == -1) {
            cout << "Errado, o número informado é maior que o número secreto.";
        }else {
            cout << "Opção inválida!";
        }

    }while(flag != 2)

}