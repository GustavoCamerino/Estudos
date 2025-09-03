#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int pid = fork();

    if (pid == 0)
    {
        printf("Olá, eu sou o filho. Esse é meu PID: %d\n", getpid());
    }
    else
    {
        printf("Olá, eu sou o pai. Esse é meu PID: %d\n", getpid());
    }

    return 0;
}
