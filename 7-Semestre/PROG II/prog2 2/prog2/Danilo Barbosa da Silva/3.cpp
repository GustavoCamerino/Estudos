// Prova 1
// Danilo Barbosa da Silva
// Questão 3

#include <iostream>
#include <vector>
#include <algorithm>

//Prototipo de funcoes
int media_vet(const std::vector &vet);  //linder: errado, vector é template
float mediana_vet(const std::vector &vet); //linder: errado, vector é template
std::vector<int> vet_moda(const std::vector &vet); //linder: errado, vector é template


// Funcao Principal
int main () {
    
    std::vector<int> vet(0);
    std::vector<int> modas_vet;
    
    int valor{0};
    std::cout << "Insira valores inteiros positivos (-1 para encerrar)"<<std::endl;
    
    // Insercao dos valores pelo o usuario
    while(valor>=0) {
        std::cin >> valor;
        if(valor >= 0) {
            vet.push_back(valor);
        }
    }

    // Impressao
    std::cout << "Media: " << media_vet(vet) << std::endl;
    std::cout << "Mediana: " << media_vet(vet) << std::endl;
    std::cout << "Moda(s): ";
    for(const auto &i : modas_vet) {
        std::cout << i << ' ';
    }

    return 0;
}

// Funcao que calcula a media
int media_vet(const std::vector &vet) { //linder: errado, vector é template
    int contador{0};
    int soma{0};
    int media{0};

    for(const auto &i : vet) {
        soma += i;
        contador++;
    }
    media = soma/contador;
    return media;
}

// Funcao que calcula a mediana
float mediana_vet(const std::vector &vet) {
    float mediana{0.0};
    float meio{0};
    
    std::sort(std::begin(vet),std::end(vet));
    meio = vet.size();
    
    if(meio%2 == 0) { //linder: % so pode ser usado com inteiro
        mediana = vet.at(meio);
        return mediana;
    } else {
        static_cast<int> (meio);
        mediana = (vet.at(meio) + vet.at(meio +1))/2; //linder: logica errada
        return mediana;
    }
}


// Funcao que retorna a moda(s)
std::vector vet_moda(const std::vector &vet) { //linder: errado, vector é template
    std::vector<int> modas_vet(0);
    int freq_atual{0};
    int freq_maxima{0};

    // Pegar a maior frequencia
    for(const auto &i : vet) {
        freq_atual = 0;
        for(const auto &j : vet) {
            if(i = j) { //errado
                freq_atual++;
            }
        }
        if(freq_atual > freq_maxima) {
            freq_maxima = freq_atual;
        }
    }

    // Verifica se existe outros valores com a mesmo frequencia
    for(const auto &i : vet) {
        freq_atual = 0;
        for(const auto &j : vet) {
            if(i = j) {
                freq_atual++;
            }
        }
        if(freq_atual == freq_maxima) {
            modas_vet.push_back(i); // Guarda no vetor de modas se freq igual a da maxima
        }
    }

    // Retorna o vetor com moda(s)
    return modas_vet;

}




/*3. (2.5 pts) Use um vector para armazenar uma lista de valores numéricos fornecidos pelo
usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular
a média dos valores, uma para calcular a mediana dos valores (valor central após
ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se,
vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível.
Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos
eles são considerados e, portanto, sua função deve retornar um vector com esses
valores. Escreva o programa principal de teste.*/