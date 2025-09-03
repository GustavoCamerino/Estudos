#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map> //nunca foi usado
using namespace std;

// usando várias coisa que nao foram ensinadas em aula.
// nao funciona!

double mean(const vector<double>& v){
    if(v.empty()) return 0.0;
    double s = 0.0;
    for(double x:v) s += x;
    return s / v.size();
}

double median(vector<double>v){
    if(v.empty()) return 0.0;
    sort(v.begin(), v.end());
    size_t n = v.size(); //linder: nunca usei size_t em aula
    if(n % 2 ==1) return v[n/2]
    else return (v[n/2 -1] + v[n/2]) /2.0;
}

vector<double> mode(const vector<double>&v){
    vector<double> res;
    if(v.empty()) return res;
    unordered_map<double,int> freq; //mapa nunca foi usado
    freq.reserve(v.size()*2);
    for(double x:v) ++freq[x];
    int maxf = 0;
    for(auto &p:freq) if(p.second > maxf) maxf = p.second;
    for(auto &p:freq) if(p.second == maxf)
res.push_back(p.first);
    sort(res.begin(), res.end());
    return res;
}

int main(){
    cout << "Entrada de valores numericos(lista de tamanho n).\n";
    int n;
    cout << "Informe quantos valores vai inserir:";
    if(!(cin >> n) || n < 0){
        cerr << "Entrada Invalida.\n";
        return 1;
    }

    vector<double>v;
    v.reserve(n);
    for(int i = 0; i < n; ++i){
        double x; cout << "Valor" << (i+1) << ":"; cin >> x;
        v.push_back(x)
    }

    cout << "\nMedia:" << mean(v) << "\n";
    cout << "Mediana:" << median(v) << "\n";
    vector<double> m = mode(v);
    cout << "Moda(Valores com maior frequencia):";
    for(size_t != 0;i<m.size();++i){
        if(i) cout << ",";
        cout << m[i];
    }
    cout << "\n";
    return 0;
}