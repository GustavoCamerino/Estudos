// Compara inteiros usando comandos IF
#include <iostream> 

using std::cout; // programa usa cout
using std::cin; // programa usa cin

int main() {
   int numero1{0}; // primeiro inteiro a ser comparado
   int numero2{0}; // segundo inteiro a ser comparado
   
   cout << "Entre com dois inteiros: "; 
   cin >> numero1 >> numero2; // lê dois inteiros

   if (numero1 > numero2) {
      cout << numero1 << " > " << numero2 << "\n";
   } else {
      cout << numero1 << " <= " << numero2 << "\n";
   } 
} 

