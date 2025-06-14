#include <unistd.h>
#include <stdio.h>

#define BSIZE 100 // Definição de um tamanho máximo para o buffer

int main()
{
    char buffer[BSIZE]; // Declaração de um array de caracteres (buffer) com o tamanho definido por BSIZE (100).
    int n;              // Variável para armazenar o número de bytes lidos.

    n = read(0, buffer, BSIZE);
    /*
    A função `read` lê os dados de um arquivo descritor (neste caso, o stdin) e armazena no buffer.
    Parâmetros:
    - `0`: É o descritor do arquivo para leitura (0 representa a entrada padrão, stdin).
    - `buffer`: É o ponteiro para o buffer onde os dados lidos serão armazenados.
    - `BSIZE`: É o número máximo de bytes que a função deve ler. Neste caso, até 100 bytes.
    Retorno:
    - `n`: Quantidade de bytes efetivamente lidos. Se for -1, indica um erro.
    */

    write(1, buffer, n);
    /*
    A função `write` escreve os dados para um arquivo descritor (neste caso, o stdout).
    Parâmetros:
    - `1`: É o descritor do arquivo para escrita (1 representa a saída padrão, stdout).
    - `buffer`: Ponteiro para o buffer que contém os dados a serem escritos.
    - `n`: O número de bytes a serem escritos, que foi o número de bytes lidos pela função `read`.
    Retorno:
    - Número de bytes escritos ou -1 em caso de erro.
    */

    return 0; // Indica que o programa terminou corretamente.
}
