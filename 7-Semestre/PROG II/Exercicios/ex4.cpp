#include <iostream>
#include <iomanip>

int main(int argc, char const *argv[])
{

    std::cout << std::setw(7) << "Número:" << std::setw(10) << "Quadrado:" << std::setw(6) << "Cubo:" << std::endl;

    for (int i = 0; i < 6; i++)
    {
        std::cout << std::setw(4) << i << std::setw(9) << i * i << std::setw(8) << i * i * i << std::endl;
    }

    return 0;
}
