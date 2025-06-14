// Realiza a adicao de dois números inteiros.
#include <iostream>
int main()
{
   // declarando e inicializando variáveis
   int numero1{0};
   int numero2{0};
   int soma{0};

   std::cout << "Entre com o primeiro inteiro: ";
   std::cin >> numero1;

   std::cout << "Entre com o segundo inteiro: ";
   std::cin >> numero2;

   soma = numero1 + numero2;

   std::cout << "Soma é " << soma << "\n";
}