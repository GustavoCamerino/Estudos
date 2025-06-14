/**
 * @file my_program.c
 * @brief Implementação de um shell simples.
 *
 * Este programa implementa um shell simples que permite mudar de diretório,
 * imprimir o diretório atual, definir e exibir uma variável de ambiente
 * chamada CAMINHO, executar comandos externos e executar comandos com pipe.
 *
 * @author Gustavo Camerino
 * @date 2024-09-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <stddef.h>

#define MAX_LINE 1024 ///< Tamanho máximo da linha de comando.
#define MAX_ARGS 100  ///< Tamanho máximo dos argumentos.

char *caminho = NULL; ///< Variável CAMINHO para procurar programas

/**
 * @brief Muda o diretório atual.
 *
 * Essa função altera o diretório atual do processo para o diretório especificado
 * como argumento.
 *
 * @param args Array de strings que contém o comando e o diretório de destino.
 */
void mudar_diretorio(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Uso: cd <diretorio>\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("Erro ao mudar de diretório");
        }
    }
}

/**
 * @brief Imprime o diretório atual.
 *
 * Essa função exibe o caminho do diretório atual no terminal.
 */
void imprimir_diretorio()
{
    char cwd[MAX_LINE];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("Erro ao obter o diretório atual");
    }
}

/**
 * @brief Define ou exibe a variável de ambiente CAMINHO.
 *
 * Essa função define a variável CAMINHO com o valor fornecido ou exibe seu valor
 * atual se nenhum argumento for fornecido.
 *
 * @param args Array de strings que contém o comando e o novo valor para CAMINHO.
 */
void definir_caminho(char **args)
{
    if (args[1] == NULL)
    {
        if (caminho != NULL)
        {
            printf("CAMINHO=%s\n", caminho);
        }
        else
        {
            printf("CAMINHO não está definido.\n");
        }
    }
    else
    {
        caminho = strdup(args[1]);
    }
}

/**
 * @brief Executa um comando externo.
 *
 * Essa função cria um processo filho para executar um comando externo.
 *
 * @param args Array de strings que contém o comando a ser executado.
 */
void executar_comando_externo(char **args)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // Processo filho - tenta executar o comando
        if (execvp(args[0], args) == -1)
        {
            perror("Comando não encontrado");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // Falha no fork
        perror("Erro ao criar processo filho");
    }
    else
    {
        // Processo pai - espera o filho terminar
        wait(NULL);
    }
}

/**
 * @brief Executa comandos com pipe.
 *
 * Essa função executa dois comandos em um pipeline, redirecionando a saída do
 * primeiro comando para a entrada do segundo.
 *
 * @param args1 Array de strings que contém o primeiro comando.
 * @param args2 Array de strings que contém o segundo comando.
 */
void executar_comando_pipe(char **args1, char **args2)
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Erro ao criar pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        // Primeiro processo
        dup2(fd[1], STDOUT_FILENO); // Redireciona saída padrão para o pipe
        close(fd[0]);
        close(fd[1]);
        execvp(args1[0], args1);
        perror("Erro no comando 1");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        // Segundo processo
        dup2(fd[0], STDIN_FILENO); // Redireciona entrada padrão para o pipe
        close(fd[0]);
        close(fd[1]);
        execvp(args2[0], args2);
        perror("Erro no comando 2");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}

/**
 * @brief Compila e executa um programa C.
 *
 * Essa função verifica se um arquivo C precisa ser recompilado com base na
 * data de modificação do arquivo fonte e do binário. Se necessário, compila o
 * programa e o executa.
 *
 * @param prog Nome do arquivo fonte (sem extensão) a ser compilado e executado.
 */
void compilar_executar_programa(char *prog)
{
    char bin[MAX_LINE];
    snprintf(bin, sizeof(bin), "./%s", prog);

    struct stat c_stat, bin_stat;

    if (stat(prog, &c_stat) == -1)
    {
        perror("Arquivo .c não encontrado");
        return;
    }

    int recompilar = 1; // Assumimos que precisa compilar

    if (stat(bin, &bin_stat) == 0)
    {
        // Se o binário já existe, verificamos as datas de modificação
        if (difftime(c_stat.st_mtime, bin_stat.st_mtime) <= 0)
        {
            recompilar = 0; // Não precisa compilar, binário está atualizado
        }
    }

    if (recompilar)
    {
        // Compilar o arquivo .c
        char comando[MAX_LINE];
        snprintf(comando, sizeof(comando), "gcc %s.c -o %s", prog, prog);
        system(comando);
    }

    // Executar o binário
    pid_t pid = fork();
    if (pid == 0)
    {
        execl(bin, prog, NULL);
        perror("Erro ao executar o programa");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
}

/**
 * @brief Interpreta e executa um comando.
 *
 * Essa função analisa a linha de comando fornecida e executa o comando correspondente,
 * que pode ser um comando interno ou um programa externo.
 *
 * @param line Linha de comando a ser interpretada e executada.
 */
void interpretar_comando(char *line)
{
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    // Separar os argumentos por espaço
    token = strtok(line, " \n");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    if (args[0] == NULL)
        return;

    // Comando interno 'cd'
    if (strcmp(args[0], "cd") == 0)
    {
        mudar_diretorio(args);
    }
    // Comando interno 'pwd'
    else if (strcmp(args[0], "pwd") == 0)
    {
        imprimir_diretorio();
    }
    // Definir ou exibir o CAMINHO
    else if (strcmp(args[0], "CAMINHO") == 0)
    {
        definir_caminho(args);
    }
    // Verificar se é um programa C
    else if (strstr(args[0], ".c") != NULL)
    {
        compilar_executar_programa(args[0]);
    }
    // Comandos com pipe
    else
    {
        executar_comando_externo(args);
    }
}

/**
 * @brief Função principal do programa.
 *
 * Esta função inicia o shell, aceita entradas do usuário e interpreta os comandos.
 */
int main()
{
    int width = 50; // Largura do caminho
    int i;

    // Movimento para a direita
    for (i = 0; i < width; i++)
    {
        printf("\033[H\033[J");
        for (int j = 0; j < i; j++)
            printf(" ");
        printf("🚗");
        usleep(100000);
        fflush(stdout);
    }

    // Movimento de volta para a esquerda
    for (i = width; i >= 0; i--)
    {
        printf("\033[H\033[J");
        for (int j = 0; j < i; j++)
            printf(" ");
        printf("🚗");
        usleep(100000);
        fflush(stdout);
    }

    char line[MAX_LINE];
    printf("\033[1;32m Camerino's Shell\033[0m\n");
    char nome[50];
    printf("Digite seu nome: ");
    scanf("%49s", nome);
    getchar();

    while (1)
    {
        printf("%s-Shell> ", nome);
        if (fgets(line, MAX_LINE, stdin) == NULL)
        {
            break;
        }
        interpretar_comando(line);
    }

    return 0;
}