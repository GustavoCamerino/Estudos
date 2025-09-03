(2.5 pts) Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio 
de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para 
isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma 
variável global. Crie a função int tentativa(int chute) que compara o chute do 
usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário 
chutou alto e -1 se o usuário chutou baixo. Use uma variável está ca para contar 
quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o 
jogador acerte, exiba também o total de tenta vas usadas. Caso o jogador erre, 
informe se o chute foi alto ou baixo. O programa deve permi r que o usuário con nue 
tentando até acertar.

#include <iostream>
#include <random>
//linder: nao funciona
int tentativa(int chute){
    int numero_secreto; //linder: nem sorteou aleatório
    int n;
    int n_tentativas = 0;

    while(n != numero_secreto){

    cout << "Insira um número: " << endl;
    cin >> n;
        for (int i = 0; i < n; i++){
            if (numero_secreto == n){
                cout << "Parabens você acertou..." << endl;
                n_tentativas += i;
                cout << "Numero de vezes em que o usuario tentou..." << n_tentativa
                return 0;
            
            } else if (numero_secreto > n) {
                cout << "Você chutou alto...." << endl;
                return 1;
            } else if(numero_secreto > n) {
                cout << "Você chutou muito alto..." << endl;
                return -1;
            }
            n_tentativas += i;
            cout << "Numero de vezes em que o usuario tentou..." << n_tentativas;
        }
    }
}

int main(){
    int n;
    int n_secreto;
    n_secreto = random(1, 100);

    n_tentativas(n_secreto);

    return 0;
}