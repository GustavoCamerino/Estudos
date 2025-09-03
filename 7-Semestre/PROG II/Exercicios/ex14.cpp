#include <iostream>
#include <string>
using namespace std;

int main()
{
    string palavraA;
    string palavraB;

    getline(cin, palavraA);
    getline(cin, palavraB);

    if (palavraA.find(palavraB) != string::npos)
    {
        cout << "Palavra B foi encontrada em Palavra A!" << endl;
    }
    else
    {
        cout << "Palavra A não encontrada!" << endl;
    }

    return 0;
}
