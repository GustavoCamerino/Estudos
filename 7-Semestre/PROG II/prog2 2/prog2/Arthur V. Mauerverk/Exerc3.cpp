#include <iostream>
#include <format>
#include <vector>

using namespace std;

/*
(2.5 pts) Use um vector para armazenar uma lista de valores numéricos fornecidos pelo 
usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular 
a média dos valores, uma para calcular a mediana dos valores (valor central após 
ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se, 
vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível. 
Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos 
eles são considerados e, portanto, sua função deve retornar um vector com esses 
valores. Escreva o programa principal de teste. 
*/

void media(int& valores);

int main(){

    vector<int, 5> valores; //linder: nao sabe definir vector!
    
    float media_valores;

    for (i = 0; i <= vector.size(); i++){ //linder: tudo errado!

        cout << "Digite um valor: " << endl;
        cin >> valores.at(i); 

    }

    media_valores = media(valores);
    valores::sort(begins(valores.at(0)), ends(valores.at(4))); //linder: errado

    return 0;
}

float media(int valores){ //linder: errado

    int soma = 0;
    for (int valor: valores){
        soma += valor;
    }

    media_valores = soma / valores.size();
    
    return media_valores;

}