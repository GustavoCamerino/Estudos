#include <iostream>
#include <string>
using namespace std;

// Prototipos
string concatena(string a, string b);

int main(int argc, char const *argv[])
{
    string palavra1;
    string palavra2;

    cout << "Digite a palavra 1: ";
    getline(cin, palavra1);

    cout << "Digite a palavra 2: ";
    getline(cin, palavra2);

    string palavraConcatenada = concatena(palavra1, palavra2);

    cout << "Palavra concatenada: " << palavraConcatenada << endl;
    return 0;
}

string concatena(string a, string b)
{
    return (string)a + b;
}