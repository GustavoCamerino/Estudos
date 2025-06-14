#include <stdio.h>
#include <unistd.h>
/*
    Todo programa já possui 3 arquivos abertos:
    entrada/teclado(0), saída/terminal(1) e err(2)
*/
int main()
{
    char buff[255];
    int n;
    while ((n = read(0, buff, 255)) > 0)
    {
        write(1, buff, n);
    }
}