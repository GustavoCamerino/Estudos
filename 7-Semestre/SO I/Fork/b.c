#include <stdio.h>
#include <unistd.h>

int main()
{
    int id;
    for (int i = 0; i < 2; i++)
    {
        id = fork();
        if (id == 0)
        {
            printf("Filho Gerado <Filho ID:%d>\n", getpid());
        }
    }

    return 0;
}