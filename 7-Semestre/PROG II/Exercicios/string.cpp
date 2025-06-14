#include <iostream>
#include <format>

int main(int argc, char const *argv[])
{
    int idade{25};
    char sexo{'M'};

    std::cout << std::format("Nome: {}, Sexo: {} \n", nome, sexo);
    return 0;
}
