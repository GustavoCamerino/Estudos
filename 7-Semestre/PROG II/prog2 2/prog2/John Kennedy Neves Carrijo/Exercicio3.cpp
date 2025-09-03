#include <iostream>
#include <format>
#include <vector>
#include <alghoritime>

//linder: errado
float moda(std :: vector <float>  &numeros){
    float num_igual{0};
    std :: sort(std :: begin numeros,std :: end numeros);
    for(int i{0};i<numeros.size();i++){
        if(numeros.at(i)==numeros.at(i+1)){
            num_igual=numeros.at(i);
        }
    }

    return num_igual;
}

//linder: ok
float media(std :: vector<float>&numeros){
    float soma{0};
    for(auto &cont:numeros){
        soma+=cont;
    }

    float media=soma/numeros.size();

    return media;
}

//linder: nao funciona
float mediana(std :: vector <float>&numeros){
    std :: sort(std :: begin numeros , std :: end numeros); //linder: errado
    int total{0};
    float mediana{0};
    for(auto &cont: numeros){
        if(cont\2==0){
            mediana=cont+(cont+1)/2;
        }else{
            mediana=cont/2;
        }
    }

    return mediana;
}


int main(){
    
    std :: vector <float> elementos;

    for(auto &cont:elementos){
        std :: cin >> cont;
        if(cont ==-1) break;
    }

    float med=media(elementos);//media
    float mod=moda(elementos);//moda
    float medi=mediana(elementos);//mediana

    std :: cout << std :: format("Media:{:.2f}\n",med);
    std :: cout << std :: format("Moda:{:.2f}\n",mod);
    std :: cout << std :: format("Mediana:{:.2f}\n",medi);
    
    return 0;
}