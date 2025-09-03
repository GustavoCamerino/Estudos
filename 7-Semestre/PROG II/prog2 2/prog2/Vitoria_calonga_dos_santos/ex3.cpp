/**
 * @author Vitoria Calonga dos Santos
 * @brief  Use um vector para armazenar uma lista de valores numéricos fornecidos pelo 
    usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular 
    a média dos valores, uma para calcular a mediana dos valores (valor central após 
    ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se, 
    vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível. 
    Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos 
    eles são considerados e, portanto, sua função deve retornar um vector com esses 
    valores. Escreva o programa principal de teste. 
*/
#include <iostream>
#include <vector>
#include <format>

int mediana(const std::vector<int> &v);
float media(const std::vector<int> &v);
std::vector moda(const std::vector<int> &v); //linder:Erro! nao especificou o template

int main(){
    std::vector<int> valores{0}, modas{0};
    int valor{0};

    //como nao foi fornecido o tipo dos valores numericos, estou considerando somente os valores inteiros,
    //porem o cin acaba capturando a parte inteira do valor fornecido e armazenando no vector, 
    //mesmo o usuario digitando um valor "invalido" e só para depois que detecta o "." o loop para...
    //quando fiz essa questao na lista pesquisei sobre o cin.peck, ele "espia" o que vem depois da parte inteira 
    //garantindo que nenhuma parte inteira de um numero decimal entre no vector
    
    //linder: vc poderia apenas considerar que o usuario sempre entra com valor valido
    while((std::cin>>valor) && (cin.peck() != ".")){ //linder::erro! sintaxe
        valores.pushback(valor); //Erro: sintaxe!
    }

    std::sort(valores.begin(),valores.end());

    modas = moda(valores); 

    std::cout << std::format("Media: {}\nMediana: {}\nModa(s): ", media(valores), mediana(valores));

    for(int i: modas){
        std::cout << i << " ";
    }

    std::cout << std::endl;
    return 0;
}

//linder: ok
float media(const std::vector<int> &v){
    int soma {0}, cont{0};
    float media{0.0f};

    for(int valor: v){
        soma += valor;
        cont++;
    }

    media = soma/cont;

    return media;
}

//linder: erro de lógica
int mediana(const std::vector<int> &v){
    int cont = v.size();
    int mediana{0}, meio {0};
    meio = cont / 2;
    if((cont % 2) == 0){
        mediana = (v.at(meio) + v.at(meio+1)) /2; //linder:erro! v.at(meio - 1)
    }else{
        mediana = v.at(meio + 1); //linder: erro! v.at(meio)
    }

    return mediana;
}

// Erro! logica implementada nao funciona.
std::vector moda(const std::vector<int> &v){ // erro! definicao do retorno
    std::vector<int> modas{0};

    int freq_max{0}, freq_atual{0};

    for(int i{0}; i < v.size(); i++){

        if(v.at(i) == v.at(i + 1)){
            freq_atual ++;
        }else{

            if(freq_atual > freq_max){
                freq_max = freq_atual;
                modas.clear();
                modas.pushback(i); //erro! sintax.
            }else if(freq_atual == freq_max){
                modas.pushback(i); //erro! sintax.
            }

            freq_atual = 0;
        }
    }

    return modas;
}