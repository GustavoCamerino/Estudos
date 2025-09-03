#include <iostream>
#include <vector>
#include <algoritm> //linder: algorithm
#include <format>

double calculaMedia(const std::vector<double> &lista);
double calculaMediana(const std::vector<double> &lista);
std::vector<double> calculaModa(const std::vector<double> &lista);

int main(){
    std::vector<double> listaValores(0);
    std::vector<double> modaValores(0);
    double entrada;

    //Obter dados
    std::cout << "Informe um valor (informe um character para encerrar):";
    std::cin >> entrada;
    //Enquanto a entrada for numerica
    while(std::typeof(entrada) = double || std::typeof(entrada) = int || std::typeof(entrada) = float){
        listaValores.push_back(entrada);

        std::cout << "Informe um valor (informe um character para encerrar):";
        std::cin >> entrada;
    }

    //Testar funcoes
    std::cout << std::format("A media dos valores e: {}", calculaMedia(listaValores)) << std::endl;
    std::cout << std::format("A mediana dos valores e: {}", calculaMediana(listaValores)) << std::endl;

    modaValores = calculaModa(listaValores);
    if(modaValores.size() == 1){
        std::cout << std::format("A moda dos valores e: {}", modaValores.at(0)) << std::endl;
    }
    else{
        std::cout << "A moda dos valores e:";
        for(double moda : modas){
            std::cout << " " << moda;
        }
        std::cout << std::endl;
    }
   
    

    return 0;
}

double calculaMedia(const std::vector<double> &lista){
    double soma {0.0};
    for(double valor : lista)
    {   
        soma += valor;
    }

    return (soma / vector.size()); //linder: lista!
}

double calculaMediana(const std::vector<double> &lista){
    double mediana {0.0};

    //Ordenar lista
    std::vector<double> listaOrdenada(0);
    listaOrdenada = lista;
    std::sort(std::begin(listaOrdenada), std::end(listaOrdenada));
    int posCentro = static_cast<int>(lista.size() / 2);
    
    //Se for impar
    if(posCentro % 2 != 0){
        mediana = vector.at(posCentro); //linder: lista nao vector
    }
    //Se for par 
    else{
        mediana = (vector.at(posCentro) + vector.at(posCentro - 1)) / 2; //linder: lista
    }
      
    return mediana;
}

//linder: não vejo a lógica para funcionar
std::vector<double> calculaModa(const std::vector<double> &lista){
    //Vars axuliares
    std::vector<double> modas(0);
    std::vector<double> amostras(0);

    //Ordenar lista
    std::vector<double> listaOrdenada = lista;
    std::sort(std::begin(listaOrdenada), std::end(listaOrdenada));
    
    //Identificar quais sao as amostras
    for(int i{0}; i < (listaOrdenada.size() - 1); i++){
        if(listaOrdenada.at(i) != listaOrdenada.at(i + 1)){
            amostras.push_back(listaOrdenada.at(i));
        }
    }
    //Se o ultimo for diferente do penultimo (o for acima nao verifica o ultimo numero)
    if(listaOrdenada.at(listaOrdenada.size() - 1) != listaOrdenada.at(listaOrdenada.size() - 2)){
        //O ultimo elemento tambem e uma amostra
        amostras.push_back(listaOrdenada.at(listaOrdenada.size() - 1));
    }

    //Verificar quantas vezes cada amostra aparece
    std::vector<double> frequencias(amostras.size());
    int contAux = 0;
    //Pra cada amostra
    for(int posAmostra{0}; posAmostra < amostras.size(); posAmostra++){
        //Iterar pela lista inteira 
        for(int i{0}; i < listaOrdenada.size(); i++){
            //Verificar e incrementar frequencia
            if(amostras.at(posAmostra) == listaOrdenada.at(i)){
                contAux ++;
                frequencias.at(posAmostra)  = contAux;
            }
        }
        //Zerar contador
        int contAux = 0;
    }

    //Identificar maior frequencia e sua pos em frequencias
    int maiorFreq {frequencias.at(0)};
    for(int valor : frequencias){
        if(valor > maiorFreq){
            maiorFreq = valor;
        }
    }

    //Identificar se a lista e multimodal e guardar as modas/moda no retorno da funcao
    //Iterar pelas frequencias
    for(int i{0}; i < frequencias.size(); i++){
        if(frequencias.at(i) == maiorFreq){
            modas.push_back(amostras.at(i));
        }
    }

    return modas;
}