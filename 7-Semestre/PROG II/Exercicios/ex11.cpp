#include <iostream>
using namespace std;

int geraAleatorio();

int main(int argc, char const *argv[])
{
    int gamestatus{0};
    cout << "Digite 1 se quiser aprender tabuada: ";
    cin >> gamestatus;

    while (gamestatus == 1)
    {
        int numberA = geraAleatorio();
        int numberB = geraAleatorio();

        int chute{0};
        int produto = numberA * numberB;
        cout << "Quanto é " << numberA << " x " << numberB << "? ";
        cin >> chute;

        while (chute != produto)
        {
            cout << "Tente novamente!" << endl;
            cout << "Quanto é " << numberA << " x " << numberB << "? ";
            cin >> chute;
        }
        if (chute == produto)
        {
            cout << "Muito bom!!!\n| Se quiser jogar novamente digite 1 | Se não digite 0 | " << endl;
            cin >> gamestatus;
        }
    }
    cout << "Obrigado por jogar!" << endl;
    return 0;
}

int geraAleatorio()
{
    int random = rand() % 11;
    return random;
}