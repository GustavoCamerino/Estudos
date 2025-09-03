#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para memset
#include <unistd.h> // Para sleep (opcional)
#include <time.h>   // Para time_t, time, difftime

int main(int argc, char *argv[]) {
    // Verifica se a quantidade de memória em MB foi fornecida como argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <quantidade_em_MB>\n", argv[0]);
        return 1; // Retorna erro se o argumento não for fornecido
    }

    // Converte o argumento da linha de comando para um número inteiro
    int mb_to_allocate = atoi(argv[1]);

    // Verifica se o valor de MB é positivo
    if (mb_to_allocate <= 0) {
        fprintf(stderr, "A quantidade de MB deve ser um número positivo.\n");
        return 1;
    }

    // Calcula o número de bytes a serem alocados (1 MB = 1024 * 1024 bytes)
    size_t bytes_to_allocate = (size_t)mb_to_allocate * 1024 * 1024;

    printf("Tentando alocar %d MB (%zu bytes)...\n", mb_to_allocate, bytes_to_allocate);

    // Aloca a memória dinamicamente usando malloc
    char *memory_block = (char *)malloc(bytes_to_allocate);

    // Verifica se a alocação de memória foi bem-sucedida
    if (memory_block == NULL) {
        perror("Erro ao alocar memória"); // Imprime uma mensagem de erro baseada no errno
        return 1;
    }

    printf("Memória de %d MB alocada com sucesso.\n", mb_to_allocate);

    // --- Percorrer a memória ---
    // Opção 1: Percorrer a memória por um tempo determinado (exemplo: 10 segundos)
    printf("Percorrendo a memória por 10 segundos para mantê-la ativa...\n");
    time_t start_time = time(NULL);
    double elapsed_time;
    int i = 0;

    do {
        // Acessa e modifica um byte a cada iteração para garantir que a memória seja acessada
        // O acesso sequencial ou aleatório pode ser modificado aqui.
        // Usamos um simples incremento para simular escrita.
        memory_block[i % bytes_to_allocate] = (char)(i % 256);
        i++;
        // Verificamos a cada 10000 iterações (ou outro valor) para não gastar muito tempo com time()
        if (i % 10000 == 0) {
            elapsed_time = difftime(time(NULL), start_time);
        }
    } while (elapsed_time < 10.0); // Percorre por 10 segundos

    printf("Memória percorrida por aproximadamente %.0f segundos.\n", elapsed_time);

    // Opção 2 (alternativa): Percorrer a memória continuamente até o programa ser encerrado.
    // Descomente o bloco abaixo e comente a Opção 1 para usar.
    /*
    printf("Percorrendo a memória continuamente (pressione Ctrl+C para encerrar)...\n");
    while (1) {
        // Acessa e modifica cada byte do bloco para mantê-lo na RAM
        for (size_t j = 0; j < bytes_to_allocate; j++) {
            memory_block[j] = (char)(j % 256); // Modifica o byte
        }
        // sleep(1); // Opcional: Pausa por um segundo para reduzir a carga da CPU, mas manter a memória alocada
    }
    */

    // Libera a memória alocada antes de sair
    printf("Liberando a memória...\n");
    free(memory_block);
    printf("Memória liberada. Programa encerrado.\n");

    return 0; // Retorna sucesso
}