#include <iostream>
#include <random>


//(2.5 pts) Implemente um programa em C++ para o jogo da adivinhação. Faça o sorteio
//de um número randômico inteiro, que será o número secreto, na faixa de 1 a 100. Para
//isso, use as funcionalidades da biblioteca <random>. O número secreto deve ser uma
//variável global. Crie a função int tentativa(int chute) que compara o chute do
//usuário com o número secreto. Ela deve retornar 0 se o usuário acertou, 1 se o usuário
//chutou alto e -1 se o usuário chutou baixo. Use uma variável está+ca para contar
//quantas vezes a função já foi chamada. Informe se o chute foi correto ou não. Caso o
//jogador acerte, exiba também o total de tentaBvas usadas. Caso o jogador erre,
//informe se o chute foi alto ou baixo. O programa deve permiBr que o usuário conBnue
//tentando até acertar.




// NÃO ME RECORDO DE COMO USAR RANDOM NA GERAÇÃO DE NUMEROS ALEATORIOS, POR ISSO FAREI APENAS O RESTO....

int numero_secreto = aleatorio();
int numero_tentativas{0};

int aleatorio(){
    //gera numeros aleatiros em um intervalo usando a biblioteca random.
    return 0;
}

//linder: varios erros
int tentativa(int chute){
    int num = *numero_secreto;
    int chute{chute};
    if (chute == num){
        std::cout << "Parabens voce acertou" << std::endl;
        numero_tetativas += 1;
        return 0;
    }
    if else(num - chute > 50){
        std::cout << "Mais sorte na proxima... Muito longe!"
        numero_tetativas += 1;
        retun 1;
    }
    else{
        std::cout << "Mais sorte na proxima... perto!"
        numero_tetativas += 1;
        return -1;
    }
}

int main(){
    int chute;
    std::cout << "Chute um valor de 0 a 100..." << std::endl;
    std::cin >> chute;

    resutado = tentativa(chute);

    if(resultado == 0){
        int opcao;
        std::cout << "Deseja continuar? 1 para sim ou 2 para nao?" << std::endl;
        std::cin >> opcao;
        if (opcao == 1){
            main()
        }
        if else (opcao == 2){
            break
        }
        else{
            std::cout << "Valor invalido";
        }
    }
    else{
        std::cout << "Errou! quer continuar? 1 para sim e 2 para não"
        std::cin >> opcao;
        if (opcao == 1){
            main()
        }
        if else (opcao == 2){
            break
        }
        else{
            std::cout << "Valor invalido";
        }
    }
    return 0;
}

