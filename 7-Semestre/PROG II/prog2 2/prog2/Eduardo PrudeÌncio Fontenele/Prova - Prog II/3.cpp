#include <iostream>
#include <format>
#include <vector>
#include <iterator>

/*Use um vector para armazenar uma lista de valores numéricos fornecidos pelo 
usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular 
a média dos valores, uma para calcular a mediana dos valores (valor central após 
ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se,
vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível. 
Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos 
eles são considerados e, portanto, sua função deve retornar um vector com esses 
valores. Escreva o programa principal de teste.*/

float calcular_media(const std::vector<float> &lista);
float calcular_moda(const std::vector<float> &lista); //linder: retorna float
void calcular_mediana(const std::vector<float> &lista);

//linder: numero excessivo de erros
int main() {

    bool flag = true;

    // Inicializa vector que irá armazenar os valores informados pelo usuario
    std::vector<float> lista {};

    // Inicializa vector que irá armazenar o(s) numero(s) de maior frequência
    std::vector<float> modas {};

    while (flag == true) {

        // Usuario informa um numero
        int numero;
        std::cout << std::format("\nDigite um numero: ");
        std::cin >> numero;

        // Adiciona numero dentro do vector
        lista.push_back(numero);

        // Usuario escolhe se quer continuar a adicionar numeros
        char continuar; 
        std::cout << std::format("\nQuer inserir outro numero ? s/n");
        std::cin >> continuar;

        if (continuar == 's') {
            continue;
        }

        if (continuar == 'n') {
            flag = false;
        }
    }

    // Mostra a media dos valores
    float media = calcular_media(lista);
    std::cout << std::format("\nMEDIA = {:.2f}\n",media);

    // Mostra a(s) moda(s)    
    std::cout << std::format("MODA(s) = \n");
    modas = calcular_moda(lista);

    for (const float modas_encontradas: modas) {
        std::cout << std::format("{}\n",modas_encontradas);
    }

    // Calcula e mostra a média
    calcular_mediana(lista);

    return 0;

}

float calcular_media(const std::vector<float> &lista) {

    float soma = 0.0f; //linder: inicializacao tipo c
    int tamanho_lista = lista.size();
    
    for (const float &numeros : lista) {
        soma += numeros;
    }

    float media = soma / tamanho_lista;

    return media;
}

//linder: const nao permite alteracao
void calcular_mediana(const std::vector<float> &lista) { 

    // Ordenando vector
    std::sort(std::begin(lista) , std::end(lista));

    int tamanho_lista = lista.size();

    // Calcula mediana se for um vector de tamanho ímpar
    if (tamanho_lista % 2 != 0) {

        int posicao = 0;
        posicao = (tamanho_lista + 1) / 2;

        std::cout << std::format("\nMEDIANA = {:.2f}.\n",lista.at(posicao - 1));
    }

    // Calcula a mediana se for um vector de tamanho par
    else {

        int posicao1 = 0;
        int posicao2 = 0;

        posicao1 = (tamanho_lista / 2) + 1;
        posicao2 = (tamanho_lista / 2);

        float media = (lista.at(posicao1 - 1) + lista.at(posicao2 - 1)) / 2.0f;
        std::cout << std::format("\nMEDIANA = {:.2f}.\n",media);

    }

}

//linder: retorna float no prototipo
std::vector<float> calcular_moda(const std::vector<float> &lista) { 

    float moda = 0.0f;
    int frequencia = 0;

    // Inicializa vetor onde será armazenado a(s) moda(s)
    std::vector <float> modas {};

    for (int i{0}; i < lista.size(); i++) {
        int contador = 0;

        for (int j{0}; j < lista.size(); j++) {
            if (lista.at(i) == lista.at(j)) {
                contador++;
            }
        }

        if (contador >= frequencia) {

            frequencia = contador;
            moda = lista.at(i);
            modas.push_back(moda);
        }
    }

    return modas;


}