#include <vector>
#include <iostream>
#include <algorithm>

//prototipo das funções
float mean(const &std::vector<float>); //linder: definicao errada
float median(const &std::vector<float>);//linder: definicao errada
std::vector<float> moda(const &std::vector<float>);//linder: definicao errada

int main() {

    //declaração de variaveis
    std::vector<float> vetor;
    float x;

    std::cout << "Insira os valores para fazer as operações de média, mediana e moda. aperte CTRL + D para encerrar a inserção: " << std::endl;

    while(std::cin >> x) { //Insere valores no fim do vetor até o usuario entrar com ctrl + d
        vetor.push_back(x);
    }

    std::cout << "A média dos valores inseridos é: " << mean(vetor) << "\nA mediana dos valores inseridos é: " << median(vetor) << "\nA moda(s) dos valores inseridos é: " << moda(vetor) << std::endl;

    return 0;
}

//função que calcula a média
float mean(const &std::vector<float> vetor) {

    float media{0.0f};

    for(auto numero : vetor) { //soma todos os numeros do vetor
        media += numero;
    }
    media /= vetor.size(); //divide a somatória de todos os valores pelo tamanho do vetor(quantidade de numeros)
    return media;
}

//função que calcula a mediana
float median(const &std::vector<float> vetor) {

    //linder: errado o uso de sort
    std::vector<float> vetor_ordenado = std::sort(std::begin(vetor), std::end(vetor)); //ordena o vetor com o metodo sort de algorithm

    int meio = (int) (vetor_ordenado.size() / 2); //pega o iterador intermediario do vetor, converte para inteiro se a divisão não deu exata

    if((vetor.size() % 2) == 0) { //se o modulo do tamanho do vetor por 2 é zero, então é par, somar os dois do meio e dividir
        float mediana = (vetor_ordenado.at(meio) + vetor_ordenado.at(meio - 1))/2.0;

    } else {
        return vetor_ordenado.at(meio); //senão, pega o valor do meio do vetor e retorna
    }
}

//função que calcula a moda (IMCOMPLETA)
std::vector<float> moda(const& std::vector<float> vetor) {

    std::vector<float> vetor_ordenado = std::sort(std::begin(vetor), std::end(vetor)); //talvez o begin e end foi utilizado de forma incorreta
    std::vector<float> nums{0}; //para armazenar todos os numeros no vetor de entrada, sem adicionar repetido
    std::vector<int> repeticoes{0}; //para contabilizar quantas vezes cada numero repetiu

    for (int i{0}; i < vetor_ordenado.size(); i++) {
        for(int j = i; j < vetor_ordenado.size(); j++) {
        if(j < (vetor_ordenado.size() - 1)) {
            if(vetor_ordenado.at(j) != vetor_ordenado.at(j + 1)) { //verifica se o numero atual é diferente do seguinte(para pegar o ultimo numero da sequencia de numeros iguais)
                nums.at(j) = vetor_ordenado.at(j);
            }
        }
        }
        if(vetor_ordenado.at(j) == nums.at(i)) {
            //
        }
    }

    return nums;
}