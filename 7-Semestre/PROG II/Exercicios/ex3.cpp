#include <iostream>
#include <cmath>

/*
Resultado	            Situação
Abaixo de 17	        Muito abaixo do peso
Entre 17 e 18,49	    Abaixo do peso
Entre 18,50 e 24,99	    Peso normal
Entre 25 e 29,99	    Acima do peso
Entre 30 e 34,99	    Obesidade I
Entre 35 e 39,99	    Obesidade II (severa)
Acima de 40	            Obesidade III (mórbida)
*/

//  Prototipos
void IMC(double peso, double altura);

int main(int argc, char const *argv[])
{
    double peso;
    std::cout << "Digite seu Peso: ";
    std::cin >> peso;

    double altura;
    std::cout << "Digite sua Altura: ";
    std::cin >> altura;

    std::cout << "Sua situação é: ";
    IMC(peso, altura);
    return 0;
}

void IMC(double peso, double altura)
{
    double imc = peso / pow(altura, 2);

    if (imc < 17)
    {
        std::cout << "Muito Abaixo do Peso" << std::endl;
    }
    else if (imc >= 17 && imc <= 18.49)
    {
        std::cout << "Abaixo do Peso" << std::endl;
    }
    else if (imc >= 18.50 && imc <= 24.99)
    {
        std::cout << "Peso Normal" << std::endl;
    }
    else if (imc >= 25 && imc <= 29.99)
    {
        std::cout << "Acima do Peso" << std::endl;
    }
    else if (imc >= 30 && imc <= 34.99)
    {
        std::cout << "Obesidade Tipo I" << std::endl;
    }
    else if (imc >= 35 && imc <= 39.99)
    {
        std::cout << "Obesidade Tipo II (severa)" << std::endl;
    }
    else if (imc >= 40)
    {
        std::cout << "Obesidade Tipo III (mórbida)" << std::endl;
    }
}