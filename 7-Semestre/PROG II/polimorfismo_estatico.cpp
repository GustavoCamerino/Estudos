#include <iostream>

// Template function to print any type
template <typename T>
void imprima(const T &value)
{
    std::cout << "[Imprimindo]: " << value << "\n";
}

int main()
{
    imprima("Olá mundo");
    return 0;
}