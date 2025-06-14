#include <iostream>
#include <string.h>
using namespace std;
class Animal
{
public:
    std::string nome;
    int idade;
    std::string especie;
    void falaAnimal()
    {
        std::cout << "Eu sou um animal\n";
    }
};

class Porco : public Animal
{
public:
    void Emite_Som()
    {
        std::cout << "Oin, oinc\n";
    }
};

int main(int argc, char const *argv[])
{
    Animal meuAnimal;
    Porco meuPorco;

    meuAnimal.falaAnimal();
    meuPorco.Emite_Som();

        return 0;
}
