#include <iostrem> //linder: <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Prototipos
double ordena(const vector &vetor);//linder: vector são templates, tem que indicar o tipo vector<int>
double media(const vector &vetor);
double mediana(const vector &vetor);
double moda(const vector &vetor);

int main(int argc, char const *argv[]) //linder: nem ensinei argumento de linha de comando
{
    vector<double> vetor(tamanho) {1.0,1.2,4.5,4.3}; //linder: nao precisa do tamanho se ta inicializando


    cout<<"Media: "<<media(vetor)<<endl;
    cout<<"Mediana: "<<mediana(vetor)<<endl;
    
    return 0;
}

double ordena(const vector &vetor) //linder: vector são templates, tem que indicar o tipo vector<int>
{                                  //linder: nao pode ser const se vai ordenar, e a funcao nao teria retorno
    return (vector)sort(vector.begin(),vector.end());
}

double media(const vector &vetor) //linder: vector são templates, tem que indicar o tipo vector<int>
{
    int tamanho = vector.size(); //errado
    double soma{0};
    for(int i=0; i<tamanho; i++)
    {
        soma+=vector.at(i);
    }
    double media = soma/tamanho;
}

double mediana(const vector &vetor) //linder: vector são templates, tem que indicar o tipo vector<int>
{                                   //logica errada
    int tamanho = vector.size();
    vector<double> vetorNovo(tamanho) = ordena(vetor);
    int meio = tamanho/2;
    double mediana = vector.at(meio);
    return mediana
}

double moda(const vector &vetor)
{
    //  esqueci
}

