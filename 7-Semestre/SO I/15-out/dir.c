#include <stdio.h>  // Biblioteca padrão para funções de entrada e saída, como printf() e perror()
#include <dirent.h> // Biblioteca que contém as funções e estruturas necessárias para trabalhar com diretórios
#include <stdlib.h> // Biblioteca padrão para funções de controle de execução, como malloc() e exit()

int main()
{
    DIR *dir;             // Ponteiro para um diretório (tipo opaco que contém informações sobre o diretório)
    struct dirent *entry; // Estrutura que contém informações sobre uma entrada (arquivo ou subdiretório) dentro de um diretório

    // Abre o diretório atual (.) e armazena o ponteiro em "dir"
    dir = opendir("."); // "." representa o diretório atual

    // Verifica se houve erro ao abrir o diretório
    if (dir == NULL)
    {
        perror("Erro ao abrir diretório"); // Exibe a mensagem de erro caso o diretório não possa ser aberto
        return 1;                          // Retorna 1 para indicar que houve um erro
    }

    // Enquanto houver arquivos/subdiretórios dentro do diretório, percorra-os
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\t I-node:%lu\n", entry->d_name, entry->d_ino); // Imprime o nome de cada arquivo ou subdiretório encontrado
    }

    // Fecha o diretório após terminar de ler
    closedir(dir);

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
