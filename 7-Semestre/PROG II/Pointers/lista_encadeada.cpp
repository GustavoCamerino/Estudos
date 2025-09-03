#include <iostream>

class No
{
public:
    int valor;
    No *proximo;

    No(int umValor) : valor{umValor}, proximo{nullptr} {}
};

class Lista
{
public:
    Lista() : inicio{nullptr} {}

    bool insereInicio(int valor)
    {
        No *aux = new No(valor);
        aux->proximo = inicio;
        inicio = aux;
        return true;
    }

    bool insereFim(int valor)
    {
        No *novo = new No(valor);
        if (inicio == nullptr)
        {
            inicio = novo;
        }
        else
        {
            No *aux = inicio;
            while (aux->proximo != nullptr)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
        return true;
    }

    void imprimeLista()
    {
        No *aux = inicio;
        while (aux != nullptr)
        {
            std::cout << "Valor: " << aux->valor << std::endl;
            aux = aux->proximo;
        }
    }

    // destrutor
    ~Lista()
    {
        No *atual{inicio};
        No *seguinte{nullptr};
        while (atual != nullptr)
        {
            seguinte = atual->proximo;
            delete atual;
            atual = seguinte;
        }
    }

private:
    No *inicio;
};

int main(int argc, char const *argv[])
{
    Lista minhaLista{};
    minhaLista.insereInicio(10);
    minhaLista.insereInicio(15);
    minhaLista.insereFim(-13);
    minhaLista.insereFim(21);
    minhaLista.insereInicio(7);
    minhaLista.insereFim(1);

    minhaLista.imprimeLista();
    return 0;
}
