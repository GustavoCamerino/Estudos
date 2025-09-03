#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//linder: definicao de vector errada
double media(vector<double, x>);
double moda(vector<double, x>);
double mediana(vector<double, x>);

double media(vector<double, vet>) { //linder: incompativel com o prototipo

    double soma {0};
    double media {0};
    double tam_vet = vet.size();

    for(int i = 0; i < vet.size(); i++) {
        soma += vet.at(i);
    }
    
    media = soma / tam_vet;

    return media;
}

//linder: nao funciona, devia retornar um vector
double moda(vector<double, vet>) {

    double maior_frequencia {0};
    vector<double, moda>;

    for(int i = 0; i < vet.size(); i++) {
        double frequencia {0};
        for(int j = 0; j < vet.size(); j++) {
            if(vet.at(i) == vet.at(j)) {
                frequencia++;
            }if(frequencia > maior_frequencia) {
                maior_frequencia = frequencia;
                moda.push_back(vet.at(i));
            }else if(frequencia == maior_frequencia) {
                moda.push_back(vet.at(i));
            }
        }
    }

    return vector(double, moda);

}

//linder: errado!
double mediana(vector<double, vet>) {

    vector<double, vet2> = vet.sort();
    vector<double, vet3>;
    double mediana;

    for(int i = 0; i <= vet2.size()/2; i++) {
        vet3.pus_back(vet2.at(i));
    }

    mediana = vet3.back();

    return mediana;

}


int main() {
    
    vector<double, vet>;
    double num {0};
    char flag;

    do{
        cout << "Informe um valor para a sequencia: "; << endl;
        cin >> num;
        vet.push_back(num);

        cout << "Deseja adicionar mais algum número? s para sim e n para não: "; << endl;
        cin >> flag;

    } while (flag != 'n');

}