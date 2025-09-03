#include <iostream>
#include <vector>
using namespace std;

// Função que multiplica duas matrizes A e B e retorna o resultado
vector<vector<float>> mult(const vector<vector<float>> &A, const vector<vector<float>> &B)
{
    int linhasA = A.size();
    int colunasA = A[0].size();
    int colunasB = B[0].size();

    // Matriz resultado com dimensões linhasA x colunasB, inicializada com zeros
    vector<vector<float>> resultado(linhasA, vector<float>(colunasB, 0));

    // Multiplicação matricial
    for (int i = 0; i < linhasA; i++)
    {
        for (int j = 0; j < colunasB; j++)
        {
            for (int k = 0; k < colunasA; k++)
            {
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return resultado;
}

int main()
{
    int linhasA, colunasA, linhasB, colunasB;

    // Leitura das dimensões da matriz A
    cout << "Digite as dimensoes da Matriz A (linhas colunas): ";
    cin >> linhasA >> colunasA;

    // Leitura das dimensões da matriz B
    cout << "Digite as dimensoes da Matriz B (linhas colunas): ";
    cin >> linhasB >> colunasB;

    // Verifica se a multiplicação é possível
    if (colunasA != linhasB)
    {
        cout << "IMPOSSIVEL multiplicar: colunas da Matriz A diferente de linhas da Matriz B.\n";
        return 1;
    }

    // Declaração e leitura da Matriz A
    vector<vector<float>> A(linhasA, vector<float>(colunasA));
    cout << "Digite os valores da Matriz A:\n";
    for (int i = 0; i < linhasA; i++)
    {
        for (int j = 0; j < colunasA; j++)
        {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }

    // Declaração e leitura da Matriz B
    vector<vector<float>> B(linhasB, vector<float>(colunasB));
    cout << "Digite os valores da Matriz B:\n";
    for (int i = 0; i < linhasB; i++)
    {
        for (int j = 0; j < colunasB; j++)
        {
            cout << "B[" << i << "][" << j << "]: ";
            cin >> B[i][j];
        }
    }

    // Calcula o produto das matrizes
    vector<vector<float>> resultado = mult(A, B);

    // Exibe a matriz resultante
    cout << "Matriz resultado (A x B):\n";
    for (int i = 0; i < resultado.size(); i++)
    {
        for (int j = 0; j < resultado[0].size(); j++)
        {
            cout << resultado[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
