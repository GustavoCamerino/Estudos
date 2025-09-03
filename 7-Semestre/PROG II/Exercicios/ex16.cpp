#include <iostream>
using namespace std;

// Prototipos
int calcTriangulo(double x, double y, double z);

int main(int argc, char const *argv[])
{
    double x{0}, y{0}, z{0};

    cout << "Digite (x,y,z): " << endl;
    cin >> x >> y >> z;
    cout << "Inseridos (" << x << "," << y << "," << z << ")" << endl;
    int calcula = calcTriangulo(x, y, z);
    if (calcula == 1)
        cout << "O triângulo é Equilátero!" << endl;
    else if (calcula == 2)
        cout << "O triângulo é Isósceles!" << endl;
    else if (calcula == 3)
        cout << "O triângulo é Escaleno!" << endl;
    else if (calcula == 0)
        cout << "Isso não é um triângulo!" << endl;
    return 0;
}

int calcTriangulo(double x, double y, double z)
{
    if (x < y + z && y < x + z && z < x + y)
    {
        if (x == y && y == z)
        {
            return 1; // Equilátero
        }
        else if (x == y || x == z || y == z)
        {
            return 2; // Isósceles
        }
        else
        {
            return 3; // Escaleno
        }
    }
    else
    {
        return 0;
    }
}