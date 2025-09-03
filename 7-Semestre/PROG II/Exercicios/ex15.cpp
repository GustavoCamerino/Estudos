#include <iostream>
#include <cmath>
using namespace std;

double distancia(int x1, int y1, int x2, int y2);

int main(int argc, char const *argv[])
{
    int x1{0}, y1{0}, x2{0}, y2{0};

    std::cout << "Digite as coordenadas do ponto 1 (x1 y1): ";
    std::cin >> x1 >> y1;

    std::cout << "Digite as coordenadas do ponto 2 (x2 y2): ";
    std::cin >> x2 >> y2;

    double d = distancia(x1, y1, x2, y2);
    cout << "A distância entre (" << x1 << "," << y1 << ") e (" << x2 << "," << y2 << ") é: " << d << endl;

    return 0;
}

double distancia(int x1, int y1, int x2, int y2)
{
    int distX = pow((x2 - x1), 2);
    int distY = pow((y2 - y1), 2);

    return sqrt(distX + distY);
}
