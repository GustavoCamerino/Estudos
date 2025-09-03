#include <iostream>  // Inclui a biblioteca de entrada e saída padrão (cout, cin)
using namespace std; // Permite usar cout, endl, etc., sem precisar do std::

// Declaração das funções antes do main
// Isso é necessário porque main chama essas funções
void cubo1(int *valor); // Função que recebe um ponteiro para int e calcula o cubo
void cubo2(int &x);     // Função que recebe uma referência para int e calcula o cubo

int main(int argc, char const *argv[])
{
    // Declara duas variáveis inteiras
    int x = 2;
    int y = 3;

    // Chama a função cubo1 passando o endereço de x
    // O valor de x será alterado diretamente via ponteiro
    cubo1(x);

    // Chama a função cubo2 passando y por referência
    // O valor de y será alterado diretamente via referência
    cubo2(y);

    // Imprime os valores atualizados de x e y
    cout << x << endl; // 8 (2^3)
    cout << y << endl; // 27 (3^3)

    return 0; // Indica que o programa terminou corretamente
}

// Função cubo1
// Recebe um ponteiro para int
// Calcula o cubo do valor apontado e atualiza o valor original
void cubo1(int **valor)
{
    *valor = (*valor) * (*valor) * (*valor);
    // *valor é o conteúdo do endereço passado
    // Multiplica o valor por ele mesmo 3 vezes
}

// Função cubo2
// Recebe um int por referência
// Calcula o cubo do valor referenciado e atualiza o valor original
void cubo2(int &x)
{
    x = x * x * x;
    // x é a própria variável original do chamador
}
