#include <iostream>
//  Exibe os equivalentes inteiros dos
// caracteres B C D b c d 0 1 2 $ * + e o
// caractere de espaço

int main(int argc, char const *argv[])
{
    std::cout << (int)'B' << " " << (int)'C' << " " << (int)'D' << " "
              << (int)'b' << " " << (int)'c' << " " << (int)'d' << " "
              << (int)'0' << " " << (int)'1' << " " << (int)'2' << " "
              << (int)'$' << " " << (int)'*' << " " << (int)'+' << " "
              << (int)'e' << " " << (int)' ' << std::endl;
    return 0;
}
