 #include <iostream>
 #include <iomanip> //linder: nunca foi discutida em aula

 int main(){

    std::cout << "Estimativa de e para a serie e = 1 + 1/1! + 1/2! + 1/3! + ...\n";
    int termos;
    std::cout << "Informe o numero de termos(>=1):";
    if(!(std::cin >> termos || termos < 1)){
        std::cerr << "Entrada Invalida\n";
        return 1;
    }

    long long fatorial = 1;
    double soma =1.0;

    for(int k =1; k <= termos; ++k){
        fatorial *= k;
        soma += 1.0 / static_cast<double>(fatorial); 
    }

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "Estimativa de e usando" << termos << "termos (alem do 1):" << soma << "\n";
    return 0 //falta ;


 }