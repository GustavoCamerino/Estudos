#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *m;
    int mem_size;
    int count = 0;
    if (argc < 2)
    {
        printf("Uso: %s <mem_size em KBi>\n", argv[0]);
        exit(0);
    }
    mem_size = atoi(argv[1]);
    m = (char *)malloc(mem_size * 1000);
    if (m == NULL)
    {
        printf("Erro ao alocar memória\n");
        exit(0);
    }
    printf("Memória alocada: %d KBi\n", mem_size);
    while (1)
    {
        m[count] = 'x';
        count++;
        if (count == mem_size * 1000)
        {
            count = 0;
        }
    }
    return 0;
}
