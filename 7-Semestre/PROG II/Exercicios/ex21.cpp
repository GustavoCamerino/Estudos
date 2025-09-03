#include <iostream>
#include <string>

using namespace std;

int gerarID(string grupo)
{
    static int contadorAlunos = 0;
    static int contadorProfessores = 0;

    if (grupo == "alunos")
    {
        contadorAlunos++;

        return 100 + contadorAlunos;
    }
    else if (grupo == "professores")
    {
        contadorProfessores++;

        return 200 + contadorProfessores;
    }
    else
    {
        return -1;
    }
}

int main()
{
    cout << "ID alunos: " << gerarID("alunos") << endl;           // 101
    cout << "ID alunos: " << gerarID("alunos") << endl;           // 102
    cout << "ID professores: " << gerarID("professores") << endl; // 201
    cout << "ID professores: " << gerarID("professores") << endl; // 202
    cout << "ID alunos: " << gerarID("alunos") << endl;           // 103
    cout << "ID outro: " << gerarID("outro") << endl;             // -1 (inválido)
    return 0;
}
