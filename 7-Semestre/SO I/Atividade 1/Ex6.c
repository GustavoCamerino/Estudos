/**
 * @file q6_waitpid_usage.c
 * @brief Demonstra o uso de waitpid() e discute suas vantagens sobre wait().
 *
 * O programa cria dois processos filhos com tempos de execução diferentes.
 * O processo pai usa waitpid() para esperar por um filho específico primeiro
 * (o que termina mais rápido), demonstrando a flexibilidade de waitpid().
 *
 * Compilar: gcc q6_waitpid_usage.c -o q6_waitpid_usage
 * Executar: ./q6_waitpid_usage
 */

#include <stdio.h>    // Para printf, perror
#include <stdlib.h>   // Para exit, WIFEXITED, WEXITSTATUS
#include <unistd.h>   // Para fork, sleep, getpid, getppid
#include <sys/wait.h> // Para waitpid

/**
 * @brief Função principal do programa.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main()
{
    int pid_child1, pid_child2;
    int status1, status2;

    printf("Pai (PID: %d): Iniciando...\n", getpid());

    // --- Cria o Primeiro Filho ---
    pid_child1 = fork();
    if (pid_child1 < 0)
    {
        perror("fork child1");
        return 1;
    }
    else if (pid_child1 == 0)
    {
        // Código do Filho 1
        printf("Filho 1 (PID: %d, PPID: %d): Vou dormir por 3 segundos...\n", getpid(), getppid());
        sleep(3);
        printf("Filho 1 (PID: %d): Acordei! Saindo com status 10.\n", getpid());
        exit(10);
    }

    // --- Cria o Segundo Filho ---
    pid_child2 = fork();
    if (pid_child2 < 0)
    {
        perror("fork child2");
        // Se este fork falhar, o pai ainda deve esperar pelo primeiro filho
        waitpid(pid_child1, &status1, 0);
        return 1;
    }
    else if (pid_child2 == 0)
    {
        // Código do Filho 2
        printf("Filho 2 (PID: %d, PPID: %d): Vou dormir por 1 segundo...\n", getpid(), getppid());
        sleep(1);
        printf("Filho 2 (PID: %d): Acordei! Saindo com status 20.\n", getpid());
        exit(20);
    }

    // --- Código do Processo Pai ---
    printf("Pai (PID: %d): Filhos %d e %d criados.\n", getpid(), pid_child1, pid_child2);

    // Esperando especificamente pelo Filho 2 (que terminará primeiro)
    printf("Pai (PID: %d): Esperando especificamente pelo Filho 2 (PID: %d)...\n", getpid(), pid_child2);
    pid_t terminated_pid_2 = waitpid(pid_child2, &status2, 0);

    if (terminated_pid_2 == -1)
    {
        perror("waitpid for child2");
        // Se waitpid falhar, ainda tentamos esperar pelo outro filho
        waitpid(pid_child1, &status1, 0);
        return 1;
    }
    printf("Pai (PID: %d): Filho %d (Filho 2) terminou. Status: %d\n",
           getpid(), terminated_pid_2, WEXITSTATUS(status2));

    // Agora esperando pelo Filho 1
    printf("Pai (PID: %d): Agora esperando pelo Filho 1 (PID: %d)...\n", getpid(), pid_child1);
    pid_t terminated_pid_1 = waitpid(pid_child1, &status1, 0);

    if (terminated_pid_1 == -1)
    {
        perror("waitpid for child1");
        return 1;
    }
    printf("Pai (PID: %d): Filho %d (Filho 1) terminou. Status: %d\n",
           getpid(), terminated_pid_1, WEXITSTATUS(status1));

    printf("Pai (PID: %d): Ambos os filhos terminaram. Encerrando.\n", getpid());

    return 0;
}