/**
 * @author Vitória Calonga dos Santos
 * @brief  Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio 
    de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para 
    isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma 
    variável global. Crie a função int tentativa(int chute) que compara o chute do 
    usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário 
    chutou alto e -1 se o usuário chutou baixo. Use uma variável está ca para contar 
    quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o 
    jogador acerte, exiba também o total de tenta vas usadas. Caso o jogador erre, 
    informe se o chute foi alto ou baixo. O programa deve permi r que o usuário con nue 
    tentando até acertar.
*/
#include <iostream>
#include <random>
#include <format>

int chute(int valor, int n);
int gera(int &n); //para que retornar se está atribuindo à referencia

int main(){
    int n{0};
    gera(&n); //Erro! nao deveria ter o &

    int numero{0};
    std::cout << "Tente adivinhar o numero secreto...\n";

    int verifica{0}, tentativas{0};
    bool flag = true;
    char novamente{' '};
    while(flag){
        std::cin >> valor; //linder: Erro! valor nem foi definido
        verifica = chute(valor, n);
        tentativas++;

        if(verifica == 0){
            std::cout << std::format("Parabens! Voce acertou com {} tentativas!\nDeseja jogar novamente?(S/N)\n", tentativas);
            std::cin >> novamente;

            if(novamente == 's' || novamente == || 'S'){
                std::cout << "Ok! Tente adivinhar o numero secreto...\n";
                gera(&n);
                tentativas = 0;
            }else{
                flag = false;
            }
        }else if(verifica == 1){
            std::cout << "Muito alto";
        }else{
            std::cout << "Muito baixo";
        }

        chute //erro!  ?????
    }



}

int gera(int &n){
    std::random_device seed;
    std::default_random_engine engine{seed()};
    std::uniform_int_distribution gerador{1,100}; 
    n = gerador; //linder: Erro! nao passou engine para o gerador.

    return n;
}

int chute(int valor, int n){
    if(valor == n){
        return 0;
    }else(valor > n){ //linder: erro do sintaxe
        return 1;
    }else{ //linder: erro do sintaxe
        return -1;
    }
}