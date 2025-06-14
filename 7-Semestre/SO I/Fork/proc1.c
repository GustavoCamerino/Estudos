#include <stdio.h>
#include <unistd.h>

int main()
{

    int pid = fork(); //  Cria um processo

    if (pid == 0) //  Processor Filho
    {
        printf("Processo filho <meu pid:%d>\n", getpid());
    }
    else //  Processo Pai
    {
        printf("Pai! <meu pid:%d>\n", getpid());
        //  A variável pid é o identificado do processo filho
        printf("PID do filho:%d\n", pid);
    }
    printf("FIM!\n");
    return 0;
}
