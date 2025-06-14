// soma o quadrado dos número de 1 a 10
#include <iostream>
using namespace std;

int main() {
   int x{1};
   int total{0};

   while (x <= 10) {
      int y = x * x;
      cout << y << "\n";
      total += y;
      ++x;
   } 

   cout << "Total é " << total << "\n";
} 
