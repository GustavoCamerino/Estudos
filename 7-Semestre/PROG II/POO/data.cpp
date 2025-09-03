#include <iostream>
#include "data.h"

Data::Data(int umDia, int umMes, int umAno) : dia{umDia}, ano{umAno}
{
    if (umMes >= 1 && umMes <= 12)
        mes = umMes;
    else
        mes = 1;
}

void Data::mostraData()
{
    std::cout << dia << "/" << mes << "/" << ano << std::endl;
}
