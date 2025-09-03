#include <iostream>
using namespace std //linder: falta ;

long somaserie(int n)
{
    long s=1.0, fat=1.0;
    for(int i=0;;i<n;i++) //linder: erro ;;
    {
        fat *=i;          //linder: calculo completamente errado do fatorial
        s += 1.0/fat; 
    }
    return (long)s;
}

int main(int argc, char const *argv[])
{
    int a{0};
    cout<<"Digite 1 número: ";
    cin>>a;
    cout<<"Serie: "<<somaserie(a)<<endl;
    return 0;
}
