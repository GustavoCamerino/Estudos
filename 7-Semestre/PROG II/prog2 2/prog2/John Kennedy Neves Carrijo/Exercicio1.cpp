#include <iostream>
#include <format>

//linder: deveria retornar long
//linder: nao funciona!
float calcular(long int n){

    const int um{1}: 
    int fatorial{1};
    float resul{0.0};
    for(int i{0};i<n;i++){
        resul+=um/fatorial;
        fatorial*=i;
    }

    resul=um+resul;

    return resul;
}

int main(){
    int num;
    std :: cout << "Digite um numero:";
    std :: cin >> num;

    float resul=calcular(num);

    std :: cout << std :: format("Resultado:{}\n",resul);

    return 0;
}