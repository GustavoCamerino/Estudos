#include <iostream>
typedef struct ResultadoCrediario
{
    int meses;
    double totalJurosPagos;
} ResultCred;

ResultCred calculaCrediario(double preco)
{
    double jurosMes = 0.015;
    double precoTotal = preco;

    double totalPagoJuros{0};
    int meses{0};
    double parcela{0};
    while (precoTotal > 0.00)
    {
        parcela = 50.00;
        meses++;

        double juros = jurosMes * precoTotal;
        totalPagoJuros += juros;

        double amortizacao = parcela - juros;

        if (amortizacao > precoTotal)
        {
            amortizacao = precoTotal;
        }
        precoTotal -= amortizacao;
    }
    ResultCred r;
    r.meses = meses;
    r.totalJurosPagos = totalPagoJuros;
    return r;
}

int main(int argc, char const *argv[])
{
    double preco;
    std::cout << "Digite o Preço do Produto: " << std::endl;
    std::cin >> preco;

    ResultCred r = calculaCrediario(preco);

    std::cout << "Meses para Pagar: " << r.meses << std::endl;
    std::cout << "Total de Juros Pagos: " << r.totalJurosPagos << std::endl;

    return 0;
}
