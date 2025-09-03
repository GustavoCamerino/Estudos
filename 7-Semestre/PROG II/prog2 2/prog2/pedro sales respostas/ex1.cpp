#include <iostream>
#include <format>

//PROTOTIPOS DE FUNCAO  

//funcao para calcular fatorial
double fatorial(long int n); //linder: fatorial é sempre inteiro, deveria retornar long
//funcao para calcular o numero de euler a partir da serie dada
double calcula_euler(long int num_termos);

int main(){
    //vairavel para armazenar o nuemro de termos fornecidos pelo usuario
    long int num_termos {0};

    //entrada de dados 
    std::cout << "Entre com um valor para o numero de termos :\n";
    std::cin >> num_termos ;
    
    //chamada da funcao para calcular a serie
    double euler = calcula_euler(num_termos);
    
    //saida de dados
    std::cout << std::format("e = {}\n",euler);

}

//IMPLEMENTACAOES

double fatorial(long int n){ //retorno como ponto flutuante para que a divisao na soma nao seja truncada
    //condicoes de parada da recursao{n=1 e n = 0
    if(n==1){
        return 1 ;
    }
    else if(n == 0){
        return 1 ;
    }

    return n * fatorial(n-1) ; //chamada recursiva
}


double calcula_euler(long int num_termos){
    double euler{1.0} ;
    for(long int i{1} ; i <= num_termos ; i++){
        double denominador = fatorial(i);  
        euler += 1/denominador ;
    }

    return euler ;
}