#include <iostream>
#include <vector>
#include <string>
std using namespace std;

int main(int argc, char const *argv[])
{
    vector<vector<char>>matriz(3,vector<char>(colunas));
    int gamestatus{0};
    cout<<"Digite 1 se queres jogar| Qualquer número para não jogar: ";
    cin >> gamestatus;

    while (gamestatus == 1)
    {
        int ganhou{0}
        while(ganhou == 0)
        {
            int vez{0};
        for(int i=0;i<3;i++)
        {
            for(int j=0; j<3;j++)
            {
                cout<<matriz.at(i,j); //linder: errado matriz.at(i).at(j)
            }
            cout<<endl;
        }
        if(vez%2==0)
        {
            int i=0, j=0;
            cout<<"Queres marcar X onde?: ";
            cin>> i>>j;
            if(matriz.at(i,j)=='O'){
                cout<<"Tente de novo: "<<endl;
                vez=0;
            }else{
                matriz.at(i,j)='X';
            }
        }else{
            int i=0, j=0;
            cout<<"Queres marcar O onde?: ";
            cin>> i>>j;
            if(matriz.at(i,j)=='X'){
                cout<<"Tente de novo: "<<endl;
                vez=0;
            }else{
                matriz.at(i,j)='O';
            }
        }
            //linder: testes errados
            if(matriz.at(0,0)=='X'&&matriz.at(1,1)=='X'&& matriz.at(0,0)=='X'|| matriz.at(2,0)=='X'&&matriz.at(1,1)=='X'&& matriz.at(0,2)=='X'|| matriz.at(0,0)=='X'&&matriz.at(1,0)=='X'&& matriz.at(2,0)=='X'||matriz.at(0,1)=='X'&&matriz.at(1,1)=='X'&& matriz.at(2,1)=='X'|| matriz.at(0,2)=='X'&&matriz.at(1,2)=='X'&& matriz.at(2,2)=='X'|| matriz.at(0,0)=='X'&&matriz.at(0,1)=='X'&& matriz.at(0,2)=='X'|| matriz.at(1,0)=='X'&&matriz.at(1,1)=='X'&& matriz.at(1,2)=='X'|| matriz.at(2,0)=='X'&&matriz.at(2,1)=='X'&& matriz.at(2,2)=='X')
            {
                cout<<"X ganhou"<<endl;
                ganhou = 1;
            } else if (matriz.at(0,0)=='O'&&matriz.at(1,1)=='O'&& matriz.at(0,0)=='O'|| matriz.at(2,0)=='O'&&matriz.at(1,1)=='O'&& matriz.at(0,2)=='O'|| matriz.at(0,0)=='O'&&matriz.at(1,0)=='O'&& matriz.at(2,0)=='O'||matriz.at(0,1)=='O'&&matriz.at(1,1)=='O'&& matriz.at(2,1)=='O'|| matriz.at(0,2)=='O'&&matriz.at(1,2)=='O'&& matriz.at(2,2)=='O'|| matriz.at(0,0)=='O'&&matriz.at(0,1)=='O'&& matriz.at(0,2)=='O'|| matriz.at(1,0)=='O'&&matriz.at(1,1)=='O'&& matriz.at(1,2)=='O'|| matriz.at(2,0)=='O'&&matriz.at(2,1)=='O'&& matriz.at(2,2)=='O')
            {
                cout<<"O ganhou"<<endl;
                ganhou = 1;
            }
            
        }
        cout<<"Digite 1 se queres jogar| Qualquer número para não jogar:  ";
        cin>>gamestatus;
    }
    

    return 0;
}


