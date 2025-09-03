#include <iostream>
#include <vector>
#include <format>
#include <algorithm>

// Prototipacao
double CalculaMedia(const std::vector<int> &vector);

double CalculaMediana(const std::vector<int> &vector);

std::vector<int> CalculaModa(const std::vector<int> &vector);


int main()
{
    // Flag para verificar se o usuario deseja inserir numeros no vetor
    int flag {1};
    // Variavel para receber o numero que o usuario deseja inserir
    int elemento {0};
    // Criando um vetor de inteiros
    std::vector<int> Vector {};

    // Laco para inserir elementos no vector
    while(flag){
        std::cout << "Numero que deseja inserir no vector: ";
        std::cin >> elemento;
        Vector.push_back(elemento);

        std::cout << "\nDeseja inserir mais elementos? ";
        std::cin >> flag;
    }

    // Chamando as funcoes e adicionando o valor em uma variavel
    double Media = CalculaMedia(Vector);
    double Mediana = CalculaMediana(Vector);
    std::vector<int> VectorModa = CalculaModa(vector);

    // Imprimindo a media, mediana e moda do vetor
    std::cout << std::format("A media do vetor: {} \nA mediana do vetor: {} \n A moda do vetor: ",Media,Mediana);

    // laco simplificado para percorrer e imprimir o vetor modal
    for(const auto &elemento : VectorModa){
        std::cout << elemento << " ";
    }

    return 0;
}

// funcao que calcula a media
double CalculaMedia(const std::vector<int> &vector)
{
    int tamanho {0};
    double Result {0.0};
    double soma {0.0};

    for(auto &elemento : vector){
        soma += elemento;
        tamanho++;
    }

    Result = soma / tamanho;

    return Result;
}

// Funcao para verificar a mediana de um vector
double CalculaMediana(const std::vector<int> &vector)
{
    std::sort(std::begin(vector), std::end(vector));
    
    int tamanho = vector.size();

    if(tamanho % 2 != 0){
        int posicao = tamanho / 2.0;
        return vector.at(posicao);
    } else { //linder: errado!
        int posicao = tamanho / 2;
        int retorno = (vector.at(posicao) + vetor.at(posicao + 1)) / 2.0;
        return vector.at(retorno);
    }
}

//linder: nao funciona
std::vector<int> CalculaModa(const std::vector<int> &vector)
{
    int ModaAtual {1};
    int ModaMaxima {1};

    // Ordenando o vetor
    std::sort(std::begin(vector), std::end(vector));

    // Vetor para receber a(s) moda(s)
    std::vector<int> Vec {};
    // Considerando que o primeiro elemento seria a moda
    Vec.push_back(vector.at(0));

    // Laco para percorrer todo o vector
    for(int i {1} ; i < vector.size(); i++){
        // Verificando se o numero atual e semelhante ao numero anterior
        if(vector.at(i) == vector.at(i-1)){
            ModaAtual++; // Numeros iguais em sequencia
        } else {
            ModaAtual = 1; // Numero diferentes em sequencia
        }

        // Se a moda atual e diferente da moda maxima
        if(ModaMaxima < ModaAtual){
            // Troca o valor da moda
            ModaMaxima = ModaAtual;
        // Enquanto o vector nao estiver vazio
            while(!empty(Vec)){
                // Remove os elementos do vector da moda
                Vec.pop_back();
            }
        // Adiciona o elemento modal no vector
            Vec.push_back(vector.at(i));
        } 
        // Se tiver algum elemento bimodal no vector
        if else (ModaMaxima == ModaAtual){
            Vec.push_back(vector.at(i)); // Adiciona ambos no vector
        }
    }

    return Vec;
}