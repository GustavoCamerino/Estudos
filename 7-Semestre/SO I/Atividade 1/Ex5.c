/**
 * @file q5_wait_behavior.c
 * @brief Demonstra o uso de wait() pelo processo pai e o comportamento de wait() no filho.
 *
 * O processo pai chama wait() para esperar o término de seu filho.
 * O programa também ilustra o que acontece se um processo filho tentar chamar wait().
 *
 * Compilar: gcc q5_wait_behavior.c -o q5_wait_behavior
 * Executar: ./q5_wait_behavior
 */

#include <stdio.h>    // Para printf, perror
#include <stdlib.h>   // Para exit, WIFEXITED, WEXITSTATUS
#include <unistd.h>   // Para fork, sleep, getpid, getppid
#include <sys/wait.h> // Para wait

/**
 * @brief Função principal do programa.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main()
{
    int pid;
    int status; // Variável para armazenar o status de saída do filho

    printf("Pai (PID: %d): Iniciando...\n", getpid());

    pid = fork(); // Cria um novo processo

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // --- Processo Filho ---
        printf("Filho (PID: %d, PPID: %d): Olá! Vou dormir 2s e tentar wait()...\n", getpid(), getppid());
        sleep(2); // Filho dorme um pouco.

        // Tentativa de chamar wait() no filho
        pid_t wait_result_child = wait(&status);
        if (wait_result_child == -1)
        {
            perror("Filho (PID: %d) wait(): No child processes (ECHILD esperado)\n");
            // ECHILD é o erro esperado, pois o filho não tem filhos para esperar.
        }
        else
        {
            printf("Filho (PID: %d) wait() retornou %d (inesperado se não há filhos)\n", getpid(), wait_result_child);
        }

        printf("Filho (PID: %d): Encerrando com status 123.\n", getpid());
        exit(123); // Filho termina com um status.
    }
    else
    {
        // --- Processo Pai ---
        printf("Pai (PID: %d): Filho %d criado. Esperando por ele com wait()...\n", getpid(), pid);

        // Pai chama wait() para esperar o filho terminar
        pid_t terminated_pid = wait(&status);

        if (terminated_pid == -1)
        {
            perror("Pai wait()");
            return 1;
        }

        printf("Pai (PID: %d): wait() retornou. Filho %d terminou.\n", getpid(), terminated_pid);

        // Interpreta o status de saída do filho
        if (WIFEXITED(status))
        {
            printf("Pai (PID: %d): Filho terminou normalmente com status: %d\n", getpid(), WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Pai (PID: %d): Filho foi encerrado por sinal: %d\n", getpid(), WTERMSIG(status));
        }
        else
        {
            printf("Pai (PID: %d): Filho terminou de forma desconhecida.\n", getpid());
        }

        printf("Pai (PID: %d): Encerrando.\n", getpid());
    }

    return 0;
}