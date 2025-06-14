/**
 * @file q1_fork_variable.c
 * @brief Demonstra o comportamento de variáveis após fork().
 *
 * O processo pai inicializa uma variável 'x'. Após o fork(),
 * tanto o pai quanto o filho modificam 'x' em seus respectivos contextos.
 *
 * Compilar: gcc q1_fork_variable.c -o q1_fork_variable
 * Executar: ./q1_fork_variable
 */

#include <stdio.h>  // Para printf
#include <stdlib.h> // Para exit
#include <unistd.h> // Para fork, getpid

/**
 * @brief Função principal do programa.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main()
{
    int x = 100; // Variável acessada e modificada por pai e filho.

    printf("Pai (PID: %d): Valor inicial de x = %d\n", getpid(), x);

    int pid = fork(); // Cria um novo processo

    if (pid < 0)
    {
        perror("fork"); // Exibe erro do sistema se fork() falhar.
        return 1;
    }
    else if (pid == 0)
    {
        // Código executado pelo processo filho
        printf("Filho (PID: %d): x antes da modificação = %d\n", getpid(), x);
        x = 200; // Filho modifica sua própria cópia de x.
        printf("Filho (PID: %d): x depois da modificação = %d\n", getpid(), x);
        exit(0); // Filho termina.
    }
    else
    {
        // Código executado pelo processo pai
        printf("Pai (PID: %d): x antes da modificação = %d\n", getpid(), x);
        sleep(1); // Pequena pausa para garantir que o filho geralmente imprima primeiro.
        x = 300;  // Pai modifica sua própria cópia de x.
        printf("Pai (PID: %d): x depois da modificação = %d\n", getpid(), x);
        // Não usamos wait() aqui para ilustrar a independência das execuções.
    }

    // Nota: O 'x' aqui refletirá o valor do processo que o executa, não um valor compartilhado.
    printf("Pai/Filho (PID: %d): Fim. Valor final de x = %d\n", getpid(), x);

    return 0;
}