#include <stdio.h>
#include "pessoa.h"

int main(int argc, char const *argv[])
{
    Pessoa p1;
    cadastra(&p1, "Gustavo Camerino", 21, "(66) 99233-9413");
    exibir(p1);
    return 0;
}
