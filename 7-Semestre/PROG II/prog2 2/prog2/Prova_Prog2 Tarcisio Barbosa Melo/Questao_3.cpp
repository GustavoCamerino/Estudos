#include <iostream>
#include <vector>
#include <string>

/* Use um vector para armazenar uma lista de valores numéricos fornecidos pelo 
usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular 
a média dos valores, uma para calcular a mediana dos valores (valor central após 
ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se,
vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível. 
Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos 
eles são considerados e, portanto, sua função deve retornar um vector com esses 
valores. Escreva o programa principal de teste.*/

bool Escolher();

double Media(std::vector<double>& vetor);
std::vector<double> Moda(std::vector<double>& vetor);
double Mediana(std::vector<double>& vetor);

int Tamanho_Vetor(std::vector<double>& vetor);

void Imprime_Vetor(const std::vector<double>& vetor);

int main(){

    std::vector<double> Vetor;
    bool Continua = true;
    std::string Escolha;

    do{
        int Numero;
        std::cout << "Digite um valor: ";
        std::cin >> Numero;
        std::cout << std::endl;

        Vetor.push_back(Numero);

        //Pergunta ao usuario se quer continuar a adicionar elementos ao vetor
        Continua = Escolher();

    }while(Continua == true);

    //Imprime os elementos adicionados ao vetor
    Imprime_Vetor(Vetor);

    //Imprime a Media do vetor
    std::cout << "A media dos valores do vetor eh: " << Media(Vetor) << std::endl;
    //Imprime a Moda do vetor
    std::cout << "A moda dos valores do vetor eh: " << Moda(Vetor) << std::endl;
    //Imprime a Mediana do vetor
    std::cout << "A mediana do vetor eh: " << std::endl;
    Imprime_Vetor(Moda(Vetor));

    
    return 0;
}

//linder: desnecessário, vector carrega seu proprio tamanho
int Tamanho_Vetor(std::vector<double>& vetor){

    int Contador{0};

    for(double Numero : vetor){

        Contador++;
    }

    return Contador;
}

double Mediana(std::vector<double>& vetor){

    Vetor_O = vetor.sort(); //linder: errado

    //linder: errado
    double Media_Meio = ((Vetor_O.at(Vetor_O.size()/2)) + (Vetor_O.at((Vetor_O.size()/2)+1))) / 2;

    double Meio_Exato = Vetor_O.at(((int)(Vetor_O.size()/2))+1);

    double Mediana = Media_Meio ? (Vetor_O.size() % 2) == 0 : Meio_Exato;

    return Mediana;
}

double Media(std::vector<double>& vetor){

    double Media;
    double Soma{0};
    int Contador{0};

    for(double Numero : vetor){

        Contador++;
        Soma += Numero;

    }

    Media = Soma/Contador;

    return Media;

}

//linder: nao funciona
std::vector<double> Moda(std::vector<double>& vetor){

    std::vector<double> Moda;
    std::vector<int> Vetor_Aux;

    int Ocorrencia{0};
    int Maior{0};

    int Contador_Aux{0};
    int Moda_Aux;

    double Temp;

    for(double Atual : vetor){

        for(double Numero : vetor){

            if(Numero == Atual){

                Ocorrencia++;

            }

        }

        if(Ocorrencia > Maior){

            Maior = Ocorrencia;
            
        }

        Vetor_Aux.push_back(Ocorrencia);
        Ocorrencia = 0;
    }

    for(int Atual : Vetor_Aux){

        for(int Numero : Vetor_Aux){

            if(Numero == Atual){

                Ocorrencia++;
                
            }
        }

        if(Ocorrencia > Maior){

            Maior = Ocorrencia;
            int Moda_Aux = Atual;
            
        }
        Ocorrencia = 0;
    }

    for(double Atual : vetor){

        for(double Numero : vetor){

             if(Numero == Atual){

                Ocorrencia++;
                
            }
        }

        if(Ocorrencia == Moda_Aux){

            Maior = Ocorrencia;

        }

        Moda.push_back(Atual);
        Ocorrencia = 0;
    }

    return Moda;
}
bool Escolher(){

    std::cout << "Deseja adicionar mais um numero? (sim/nao)" << std::endl;
    std::cin >> Escolha;

    if(Escolha == "sim"){

        return true;

    }else if(Escolha == "nao"){

        return false;

    }else{

        std::cout << "---OPCAO INVALIDA---" << std::endl;
        Escolher();

    }

}

void Imprime_Vetor(const std::vector<double>& vetor){

    std::cout << "---VETOR---" << std::endl;

    for(double Numero : vetor){

        std::cout << Numero << " ";

    }

    std::cout << std::endl;

}
