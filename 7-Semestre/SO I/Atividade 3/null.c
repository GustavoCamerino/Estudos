#include <stdio.h>
#include <stdlib.h> // Para EXIT_SUCCESS e EXIT_FAILURE

int main() {
    // 1. Definir um ponteiro como NULL
    int *ptr = NULL;

    printf("Ponteiro 'ptr' definido como NULL. Endereço: %p\n", (void *)ptr);

    // 2. Tentar acessar o ponteiro NULL
    // Esta operação irá resultar em um erro de segmentação (segmentation fault)
    // na maioria dos sistemas operacionais, pois estamos tentando acessar
    // uma área de memória inválida.
    printf("Tentando desreferenciar o ponteiro NULL...\n");

    // A linha abaixo causará o erro.
    // Para compilar e ver o erro em tempo de execução, precisamos incluí-la.
    // int valor = *ptr; // Esta linha causará o 'segmentation fault'

    // Se você quiser que o programa compile e execute sem falhar (e apenas mostre a intenção),
    // você pode comentar a linha acima e descomentar a próxima linha para demonstrar o que aconteceria.
    printf("Se a linha 'int valor = *ptr;' estivesse ativa, o programa provavelmente falharia aqui.\n");

    // Para evitar que o programa caia com segmentation fault imediatamente,
    // vamos apenas imprimir uma mensagem de aviso se o ponteiro for NULL antes de tentar acessá-lo.
    // No entanto, para fins de demonstrar o comportamento de um acesso a NULL,
    // a linha comentada acima (*ptr) é o que você procurava.
    if (ptr == NULL) {
        printf("Atenção: O ponteiro é NULL. Acessá-lo causaria um erro de segmentação.\n");
    }

    printf("Programa finalizado. (O segmentation fault ocorreria antes desta mensagem se a desreferência fosse feita).\n");

    return EXIT_SUCCESS; // Retorna 0 para indicar sucesso, mesmo que a intenção fosse demonstrar a falha.
                         // Se você descomentar '*ptr', o programa não chegará a este ponto.
}