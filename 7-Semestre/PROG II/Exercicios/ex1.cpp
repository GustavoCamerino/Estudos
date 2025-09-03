#include <iostream>
#include <iomanip>
#include <tuple>

using namespace std;

// Protótipo
// Agora retornando os valores individuais dos descontos para maior clareza na saída
tuple<double, double, double, double, double, double> calc_salario(double h_trab, int num_dep);

int main(int argc, char const *argv[])
{
    double h_trab;
    int num_dep;

    cout << "Digite o número de horas trabalhadas na semana: \n";
    cin >> h_trab;
    cout << "Digite o número de dependentes: \n";
    cin >> num_dep;

    double s_bruto, descontos, s_liquido;
    double previdencia, receita, estado, sindicato, seguro;

    // A função agora retorna mais valores para a exibição detalhada dos descontos
    tie(s_bruto, s_liquido, previdencia, receita, estado, sindicato) = calc_salario(h_trab, num_dep);

    // Ajusta a saída para mostrar 2 casas decimais, como em valores monetários
    cout << fixed << setprecision(2);

    cout << "\n--- RESUMO SEMANAL ---\n";
    cout << "Pagamento Bruto  : R$ " << s_bruto << endl;
    cout << "  Previdência    : R$ " << previdencia << endl;
    cout << "  Receita Federal: R$ " << receita << endl;
    cout << "  Estado         : R$ " << estado << endl;
    cout << "  Sindicato      : R$ " << sindicato << endl;

    // Adiciona o desconto do seguro apenas se ele existir
    if (num_dep >= 3)
    {
        // Obter o valor do seguro da tupla
        double seguro = get<5>(calc_salario(h_trab, num_dep));
        cout << "  Seguro Saúde   : R$ " << seguro << endl;
        s_liquido -= seguro;
    }

    descontos = previdencia + receita + estado + sindicato + (num_dep >= 3 ? 35.0 : 0.0);

    cout << "Total Descontos  : R$ " << descontos << endl;
    cout << "Pagamento Liquido: R$ " << s_liquido << endl;

    return 0;
}

tuple<double, double, double, double, double, double> calc_salario(double h_trab, int num_dep)
{
    double h_normal = 16.78;
    double h_extra = h_normal * 1.5;

    double horas_normais = 0;
    double horas_extras = 0;

    if (h_trab > 40)
    {
        horas_normais = 40;
        horas_extras = h_trab - 40;
    }
    else
    {
        horas_normais = h_trab;
    }

    double s_bruto = horas_normais * h_normal + horas_extras * h_extra;

    double previdencia = 0.06 * s_bruto;
    double receita = 0.14 * s_bruto;
    double estado = 0.05 * s_bruto;

    double sindicato = 10.0;
    double seguro = 0.0;

    if (num_dep >= 3)
    {
        seguro = 35.0;
    }

    double descontos = previdencia + receita + estado + sindicato + seguro;
    double s_liquido = s_bruto - descontos;

    // Retorna todos os valores necessários para exibição detalhada
    return make_tuple(s_bruto, s_liquido, previdencia, receita, estado, sindicato);
}