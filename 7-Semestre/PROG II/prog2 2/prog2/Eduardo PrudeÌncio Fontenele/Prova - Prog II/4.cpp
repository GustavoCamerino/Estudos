#include <iostream>
#include <random>
#include <format>

/* Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio 
de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para 
isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma 
variável global. Crie a função int tentativa(int chute) que compara o chute do 
usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário 
chutou alto e -1 se o usuário chutou baixo. Use uma variável estática para contar 
quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o 
jogador acerte, exiba também o total de tentativas usadas. Caso o jogador erre, 
informe se o chute foi alto ou baixo. O programa deve permitir que o usuário continue 
tentando até acertar.*/

int gerar_numero_aleatorio();
int tentativa(int chute);
int contador();

// Variavél global que armazenará um numero randômico
int numero_sorteado = 0;

int main() {

    bool flag = true;

    std::cout << std::format("{:_>50}\n",""); //linder: errado
    std::cout << std::format("ADIVINHE O NUMERO\n");
    std::cout << std::format("{:_>50}\n"); //linder: errado

    // Gera numero aleatório e atribui para a variavel global
    numero_sorteado = gerar_numero_aleatorio();

    while (flag == true) {

        // Usuario irá adivinhar o numero
        int chute;
        std::cout << std::format("\nAdivinhe o numero: ");
        std::cin >> chute;

        // Verificando tentativa
        int tentativa = tentativa(chute); //linder: mesmo nome para variavel e funcao

        // Conta quantas vezes o usuário "chutou" um numero
        int contador_tentativas = contador();

        if (tentativa == 1) {
            std::cout << std::format("\nMuito Alto. Tente novamente.\n");
            continue;
        }

        else if (tentativa == -1) {
            std::cout << std::format("\nMuito Baixo. Tente novamente\n");
            continue;
        }
        
        else if (tentativa == 0) {

            std::cout << std::format("\nParabéns! Você acertou o numero.\n");
            std::cout << std::format("Tentativas = {}.\n",contador_tentativas);
            flag = false;
        }
    }

    return 0;
}

int gerar_numero_aleatorio() {

    static std::random_device seed;
    static std::default_random_engine engine{seed()};
    static std::uniform_int_distribution gerador {1,100};

    int numero_aleatorio = gerador(engine);

    return numero_aleatorio; 
}

int tentativa(int chute) {

    if (chute == numero_sorteado) {
        return 0;
    }

    if (chute > numero_sorteado) {
        return 1;
    }

    if (chute < numero_sorteado) {
        return -1;
    }
}

int contador() {

    static int x{0};
    x++;

    return x;
}