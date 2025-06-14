#include <stdio.h>
int global;
int main()
{

    char *p = (char *)malloc(100);
    int x;
    printf("Código: %p\t Heap: %p\t Pilha: %p\t Global: %p\t\n", main, p, &x, &global);
    return 0;
}