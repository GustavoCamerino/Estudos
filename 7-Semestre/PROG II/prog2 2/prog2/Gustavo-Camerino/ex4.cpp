#include <iostream>
#include <random>
using namespace std;

random_device rd;
mt19937 gen(rd()); //linder: nunca foi discutido esse gerador
int i = uniform_int.distribution<> dist(1,100); //errado

static int qtd{0}; //linder: deveria ser declarado dentro da funcao, aqui nao tem sentido

int tentativa(int chute)
{
    qtd++;
    if(chute == i)
    {
        return 0;
    }else if (chute > i)
    {
        return 1;
    }else if (chute < i)
    {
        return -1;
    }else{
        return 100; //linder: ??
    } 
}

int main(int argc, char const *argv[])
{
    int gamestatus{0};
    cout<<"Digite 1 se queres jogar| Qualquer número para não jogar: ";
    cin >> gamestatus;
    while (gamestatus == 1)
    {
        int chute{0};
        int tenta{0};
        cout<<"Adivinhe o número: ";
        cin>>chute;
        tenta = tentativa(chute);
        if(tenta == 0){
            cout<<"Parabéns, você ganhou!\nDigite 1 se queres jogar| Qualquer número para não jogar: ";
            cin >> gamestatus;
        }else if(tenta == 1){
            cout<<"Chutou alto\nTente novamente...";
        }else if(tenta == -1){
            cout<<"Chutou baixo\nTente novamente...";
        }else if (tenta == 100)
        {
            cout<<"Erro número Invalido!\nTente novamente...";
        }
    }

    cout<<"Você jogou: "<<qtd<<" vezes!"<<endl;
    


    return 0;
}
