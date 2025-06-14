#ifndef PESSOA_H

#define PESSOA_H

typedef struct
{
    char Nome[100];
    int Idade;
    char Contato[100];
} Pessoa;

void cadastra(Pessoa *p, const char *Nome, int Idade, const char *Contato);
void exibir(Pessoa p);
#endif