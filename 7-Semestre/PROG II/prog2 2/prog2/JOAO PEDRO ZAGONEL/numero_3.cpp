#include <iostream>
#include <vector>

//(2.5 pts) Use um vector para armazenar uma lista de valores numéricos fornecidos pelo
//usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular
//a média dos valores, uma para calcular a mediana dos valores (valor central após
//ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se,
//vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível.
//Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos
//eles são considerados e, portanto, sua função deve retornar um vector com esses
//valores. Escreva o programa principal de teste.

//linder: vários erros!
int gerenciador(vector<int, tamanho> nome){
    int tam{tamanho};

    float media = media1(vector<int, tam> nome); 
    std::cout << "Media:" << media << std::endl;
    int moda, qntd = moda(vector<int, tam> nome);
    std::cout << "Moda(s):" << moda << ";" << qntd << std::endl;
    float mediana = mediana(vector<int, tam> nome);
    std::cout << "Mediana:" << mediana << std::endl;

    vector<float, 4> valores{media, moda, qntd, mediana};

    return valores;

}

//linder: varios erros
float media1(vector<int, tam> nome){
    for (auto &indice : nome){
        float soma += nome{indice};
        int contador += 1;
    }
    float Media = soma / contador;
    return Media;
}

//linder: varios erros
int mediana(vector<int, tam> nome){
    vectot<int, tam> nwe = vector<int, tam> nome;
    begin(nwe).end(tam);

    if (tam % 2 == 0){
        mediana = (nwe{tam / 2} + nwe{(tam /2) + 1})/2;
    }
    else{
        mediana = nwe{tam / 2 + 1};
    }
    return mediana;

}

//linder: errado
int moda(vector<int, tam> nome){
    int conta{1};
    int moda = nome{0};
    for (auto &indice : nome){
        if (moda < indice){
            moda = vector{incice};
            conta = 1
        }
        else{
            conta += 1;
        }
    }
    return moda, conta;
}

int main(){
    int quantidade;
    std::cout << "Digite uma sequencia de numeros separados por espaco. (Termiando com enter)" << std::endl;
    numeros = getline(std::cin, "\n");
    std::cout << "Digite a quantidade de numeros" << std::endl;
    std::cin >> quantidade;
    vector<int, quantidade> valores = numeros;

    gerenciador(valores);
    
    return 0;

}