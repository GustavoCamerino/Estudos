#define _USE_MATH_DEFINES // Garante que M_PI seja definido em cmath
#include <iostream>
#include <cmath>   // Para pow e sin
#include <iomanip> // Para setprecision e fixed

int main()
{
    // Declaração das variáveis e inicialização da gravidade
    double velocidadeInicial; // v0
    double anguloGraus;       // teta_graus
    double gravidade = 9.8;   // g
    double alcance;           // Distância horizontal percorrida

    // A variável 'altura' foi removida porque não é utilizada nesta fórmula de alcance do solo.
    // Se precisar calcular para lançamento de uma altura, a fórmula seria diferente.

    std::cout << "--- Cálculo do Alcance Horizontal de um Projétil ---\n";

    // Solicita a velocidade inicial ao usuário
    std::cout << "Digite a Velocidade Inicial (v0 em m/s): ";
    std::cin >> velocidadeInicial;

    // Solicita o ângulo de lançamento ao usuário
    std::cout << "Digite o Ângulo de lançamento (em graus): ";
    std::cin >> anguloGraus;

    // Converte o ângulo de graus para radianos
    // M_PI é a constante para Pi, disponível com _USE_MATH_DEFINES
    double anguloRadianos = anguloGraus * M_PI / 180.0;

    // Calcula o alcance usando a fórmula: R = (v0^2 * sin(2*theta)) / g
    // sin() espera o ângulo em radianos
    alcance = (std::pow(velocidadeInicial, 2) * std::sin(2 * anguloRadianos)) / gravidade;

    // Formata a saída para mostrar 2 casas decimais para o alcance
    std::cout << std::fixed << std::setprecision(2);

    // Exibe o resultado
    std::cout << "Distância horizontal (alcance): " << alcance << " metros." << std::endl;

    return 0; // Indica que o programa foi executado com sucesso
}