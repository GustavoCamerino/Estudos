#include <iostream>
#include <random>

//Criação do gerador de numeros aleatórios
static std::random_device seed; //aqui eu defini uma seed
static std::default_random_engine gerador{seed()}; //aqui eu usei um gerador com a seed que criei
static std::int_distribution_generator {1,100}; //aqui eu defini o intervalo de geração de numeros, o nome pode estar escrito errado
                                                 //linder: std::uniform_int_distribution<int> gerador

//variavel global com o numero secreto
int numero {gerador(engine)}; //linder: gerador nao foi definido

//variavel global estática da quantidade de chutes
static int qtd_chutes{0}; //linder: deveria ter definido dentro de tentariva

//prototipo da função
int tentativa(int chute);


int main() {

//declaração de variaveis
int x{0};
int numero{0};

std::cout << "insira um valor: " << std::endl;

//loop das tentativas até o usuário acertar
do {

//a cada execução, pega um numero do usuário e verifica se a tentativa dele deu certo
std::cin >> numero;
x = tentativa(numero);

if (x == 0) {
    std::cout << "Parabens, voce acertou!\nQuantidade de tentativas: " << qtd_chutes << std::endl;
} else if (x == -1) {
    std::cout << "Seu chute foi baixo, tente novamente: " << std::endl;
} else if (x == 1) {
    std::cout << "Seu chute foi alto, tente novamente: " << std::endl;
}

} while (x != 0); //enquanto o usuario não acertou (função tentativa não retornar 0) a adivinhação irá continuar

    return 0;
}


//função para verificar se a tentativa foi correta e/ou verificar se esta alto ou baixo
int tentativa(int chute) {

    //aumenta o valor da quantidade de chutes a cada chamada da função
    qtd_chutes++;

    //verifica se acertou, chutou alto ou baixo
    if (chute == numero) return 0;
    else if (chute > numero) return 1;
    else return -1; 
}