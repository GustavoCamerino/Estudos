#include <iostream>
#include <array>
using namespace std;

int main(int argc, char const *argv[])
{
    int vetor[5]{1, 2, 3, 4, 5};
    array<int, 5> meuArray = to_array(vetor);

    cout << "Vetor novo: " << endl;
    for (int i : meuArray)
    {
        cout << i << endl;
    }

    int x{10};
    int y{20};

    const int *ptr{&x};
    ptr = &y;

    return 0;
}
