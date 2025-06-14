// Programa de teste da classe string da biblioteca padrao C++. 
#include <iostream>
#include <string> 
using namespace std;

int main() {
   string s1{"happy"};    
   string s2{" birthday"};
   string s3; // cria uma string vazia
              
   // mostra a string e seu comprimento (C++20)
   cout << "s1: \"" << s1 << "\"; length: " << s1.length()
      << "\ns2: \"" << s2 << "\"; length: " << s2.length()
      << "\ns3: \"" << s3 << "\"; length: " << s3.length();

   // compara strings com == e !=
   cout << "\n\nComparando s2 e s1:" << boolalpha
      << "\ns2 == s1: " << (s2 == s1)
      << "\ns2 != s1: " << (s2 != s1);
   
   // testa o método empty
   cout << "\n\nTestando s3.empty():\n";

   if (s3.empty()) {
      cout << "s3 está vazio; concatenando e atribuindo a s3;\n";
      s3 = s1 + s2; 
      cout << "s3: \"" << s3 << "\"";
   } 

   // testando métodos de C++20  
   cout << "\n\ns1 começa com \"ha\": " << s1.starts_with("ha") << "\n";
   cout << "s2 começa com \"ha\": " << s2.starts_with("ha") << "\n";
   cout << "s1 termina com \"ay\": " << s1.ends_with("ay") << "\n";
   cout << "s2 termina com \"ay\": " << s2.ends_with("ay") << "\n";
} 