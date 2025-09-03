/* Use um vector para armazenar uma lista de valores numéricos fornecidos pelo 
usuário. A lista pode ter qualquer tamanho. Implemente 3 funções, uma para calcular 
a média dos valores, uma para calcular a mediana dos valores (valor central após 
ordenação) e uma para calcular a moda dos valores (valor mais frequente). Lembre-se, 
vectors podem ser grandes, portanto faça a passagem da forma mais eficiente possível. 
Além disso, no caso da moda, lembre-se de que quando há empate entre valores, todos 
eles são considerados e, portanto, sua função deve retornar um vector com esses 
valores. Escreva o programa principal de teste. */

#include <iostream>
#include <iomanip>

//linder: errado
void media (int val, num){
    for(int i = 0; i < num, i++ ){
        double soma =+ val[i];
        double medianu = soma / num;
    }

    return medianu;
}
//linder: errado!
void mediana(int val){
    double meio = num \\ 2;
    for(int val; i < num, i++){
        int median = num[meio];
        
    }
    return median;

}
//linder: errado
void moda(int val){

    int compara = val;
    int cont = 0;
    
    for(int i = 0; i < num){
        if(compara == val[i]){
            cont++
            
        }
        
    }
}


int main(){

    long int vertor = [100]; //linder: pedi para usar a classe vector
    int numeros = 0;
    bool valores = true;
    

    int valor = 0;
    std::cout << "QUANTOS VALORES SERAM DIGITADOS ? ";
        std::cin >> valor;

    for(int i = 0; i < valor; i++ ){
        std::cout << "DIGITE O NUMERO PARA A POSIÇÃO " << (i + 1) << " :" ;
        std::cin >> vetor[i];
        valor++
        numeros++
    }


    std::cout << "o valor da media é : " << media(vetor, numeros) << std::endl;
    std::cout << "o valor da mediana é : " << mediana(vetor, numeros) << std::endl;
    std::cout << "o valor da moda é : " << moda(vetor,numeros) << std::endl;

    return 0;
}