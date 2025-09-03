(2.5 pts) Use um vector para armazenar uma lista de valores numéricos fornecidos pelo 
usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular 
a média dos valores, uma para calcular a mediana dos valores (valor central após 
ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se, 
vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível. 
Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos 
eles são considerados e, portanto, sua função deve retornar um vector com esses 
valores. Escreva o programa principal de teste. 

#include <iostrem>
#include <vector>
using namespace std;

//errado!
int calcular_media(){

    int tamanho;
    int soma = 0;
    int media = 0;

    for (int i = 0; i <= tamanho; i++){
        soma += vet[i]; //linder: vet inidefinido
        return soma / tamanho;
    }
    return media;
}

int verificar_moda(){
    int moda;
    int tamanho;

    for (int i = 0; i < tamanho; i++){
        if (moda == i){
            cout << "Números que se repetem: " << moda;
        }else{
            cout << "O vetor não possui moda..." << endl;
        }
    }
    return 0;
}

int calcular_mediana(){
    int mediana;
    int tamanho;
    int vet;

    for (int i = 0; i < tamanho; i++){
        if (vet == i){
            mediana = i;
        }
    }
    return mediana;
}

int main(){
    int vet[] {5, 5, 6, 9, 12};
    int tamanho = 5;

    cout << "Media dos valores presentes: " << calcular(vet, tamanho) << endl;
    cout << "Moda dos valores: " << verificar_moda(vet, tamanho);
    cout << "Mediana dos valores: " << calcular_mediana(vet, tamanho);
    cout << "Fim..." << endl;

    return 0;
}