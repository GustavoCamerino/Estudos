#include <iostream>
#include <random>
#include <ctime> //nunca foi usado

//mais uma vez usando coisas que nao foram vistas em sala de aula.
// não funciona!

int segredo;
int tentativa(int chute){
    static int contador = 0;
    ++contador;
    if(chute == segredo){
        std::cout << "Acertou! total de tentativas(chamadas a tentativa):" << contador << "\n";
        return 0;
    } else if(chute>segredo){
        std::cout << "Chute Alto\n";
        return 1; 
    }else {
        std::cout << "Chute baixo\n";
        return -1;
    }
}

int main(){
    std::mt19937 mg(static_cast<unsigned int>(std::time(nullptr))); //nunca foi usado
    std::uniform_int_distribution<int> dist(1,100);
    segredo = dist(rng);
    std:: cout << "Jogo da Adivinhacao (numero entre 1 e 100)\n";
    int chute;
    while(true){
        std:: cout << "Informe seu chute:";
        if(!(std::cin >> chute)) {std::cout << "Entrada Invalida. Encerrando.\n"; break;}
        if(chute < 1 || chute > 100){
            std::cout << "Chute fora do intervalo 1..100.Tente novamente\n";
            continue;
        }

        int res = tentativa(chute);
        if(res ==0){
            std::cout << "Fim do jogo.Parabens!\n";
            break;
        }else {
            std::cout << "Tente novamente.\n";
        }
        return 0;
    }

}