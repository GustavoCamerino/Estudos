#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    string linha;
    cout << "Digite uma frase: ";
    getline(cin, linha); // lê a linha inteira com espaços

    istringstream iss(linha); // fluxo de entrada baseado na string
    string palavra;

    cout << "Palavras encontradas:" << endl;
    while (iss >> palavra) // separa automaticamente por espaços
    {
        cout << palavra << endl;
    }

    return 0;
}
