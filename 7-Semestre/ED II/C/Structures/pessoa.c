#include <stdio.h>
#include <string.h>
#include "pessoa.h"

void cadastra(Pessoa *p, const char *Nome, int Idade, const char *Contato)
{
    strcpy(p->Nome, Nome);
    p->Idade = Idade;
    strcpy(p->Contato, Contato);
}

void exibir(Pessoa p)
{
    printf("Nome: %s\n", p.Nome);
    printf("Idade: %d\n", p.Idade);
    printf("Contato: %s\n", p.Contato);
}