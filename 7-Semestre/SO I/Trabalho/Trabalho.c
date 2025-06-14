/**
 * @file Trabalho.c
 * @author Gustavo Camerino
 * @brief Trabalho 1 de Sistemas Operacionais
 * @version 1.0
 * @date 2024-09-20
 *
 * @copyright Copyright (c) 2024
 *
 * Shell com funcionalidades básicas como execução 
 * de comandos, manipulação de variáveis de ambiente, suporte a pipes e compilação
 * de programas em C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define TAM_MAX_CMD 1024 ///< Tamanho máximo do comando.
#define TAM_MAX_ARG 100  ///< Número máximo de argumentos por comando.
#define TAM_CAMINHO 1024 ///< Tamanho máximo do caminho.

char *var_caminho = NULL; ///< Variável global para armazenar o caminho.

/**
 * @brief Executa um comando, verificando se é um comando interno ou externo.
 *
 * Esta função verifica se o comando é a definição de uma variável de ambiente,
 * um comando interno como `cd` ou `pwd`, ou se é um comando externo. Se for
 * externo, a função cria um processo filho para executá-lo.
 *
 * @param cmd O comando a ser executado.
 */
void executar_comando(char *cmd);

/**
 * @brief Muda o diretório de trabalho atual.
 *
 * Esta função altera o diretório de trabalho para o caminho fornecido como argumento.
 * Se o caminho não for encontrado, uma mensagem de erro será exibida.
 *
 * @param caminho O novo diretório a ser acessado.
 */
void mudar_diretorio(char *caminho);

/**
 * @brief Imprime o diretório de trabalho atual.
 *
 * Esta função obtém e exibe o caminho do diretório de trabalho atual.
 */
void imprimir_diretorio_atual();

/**
 * @brief Define a variável de caminho (CAMINHO).
 *
 * Esta função armazena o valor da variável de ambiente `CAMINHO` para uso em comandos.
 * Se a variável já tiver um valor, este é substituído.
 *
 * @param nome O nome da variável (deve ser "CAMINHO").
 * @param novo_caminho O valor a ser atribuído à variável CAMINHO.
 */
void definir_variavel_caminho(char *nome, char *novo_caminho);

/**
 * @brief Imprime o valor da variável de caminho (CAMINHO).
 *
 * Exibe o valor atual armazenado na variável de ambiente `CAMINHO`.
 *
 * @param nome O nome da variável a ser impressa (deve ser "CAMINHO").
 */
void imprimir_variavel_caminho(char *nome);

/**
 * @brief Executa dois comandos conectados por um pipe.
 *
 * Esta função cria um pipe entre dois processos, executando os dois comandos
 * fornecidos. O primeiro comando escreve no pipe, enquanto o segundo lê dele.
 *
 * @param cmd1 O primeiro comando.
 * @param cmd2 O segundo comando.
 */
void executar_pipe(char *cmd1, char *cmd2);

/**
 * @brief Expande variáveis de ambiente no comando.
 *
 * Substitui o valor de variáveis como `$CAMINHO` com seus respectivos valores
 * armazenados. Se a variável `CAMINHO` estiver presente no comando, será expandida.
 *
 * @param cmd O comando que pode conter variáveis a serem expandidas.
 * @return O comando com as variáveis expandidas.
 */
char *expandir_variaveis(char *cmd);

/**
 * @brief Função principal do shell.
 *
 * Esta função executa o loop principal do shell, que lê e executa comandos do
 * usuário até que o shell seja encerrado.
 *
 * @return Retorna 0 ao terminar a execução.
 */
int main()
{
    int largura = 50; // Largura do caminho
    int i;
    for (i = largura; i >= 0; i--)
    {
        printf("\033[H\033[J");
        for (int j = 0; j < i; j++)
            printf(" ");
        printf("🚗");
        usleep(100000);
        fflush(stdout);
    }
    printf("\n");

    printf("#-------------------------------------------------------------------------------------------------------------------------------# \n");
    printf("▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖    ▗▄▄▄▖▗▄▖      ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖ ▗▄▖  ▗▄▄▖     ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   \n");
    printf("▐▌ ▐▌▐▌   ▐▌   ▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌         █ ▐▌ ▐▌    ▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌   ▐▌ ▐▌  █  ▐▛▚▖▐▌▐▌ ▐▌▐▌       ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌   \n");
    printf("▐▌ ▐▌▐▛▀▀▘▐▌   ▐▌   ▐▌ ▐▌▐▌  ▐▌▐▛▀▀▘      █ ▐▌ ▐▌    ▐▌   ▐▛▀▜▌▐▌  ▐▌▐▛▀▀▘▐▛▀▚▖  █  ▐▌ ▝▜▌▐▌ ▐▌ ▝▀▚▖     ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   \n");
    printf("▐▙█▟▌▐▙▄▄▖▐▙▄▄▖▝▚▄▄▖▝▚▄▞▘▐▌  ▐▌▐▙▄▄▖      █ ▝▚▄▞▘    ▝▚▄▄▖▐▌ ▐▌▐▌  ▐▌▐▙▄▄▖▐▌ ▐▌▗▄█▄▖▐▌  ▐▌▝▚▄▞▘▗▄▄▞▘    ▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖\n");
    printf("#-------------------------------------------------------------------------------------------------------------------------------# \n");
    char cmd[TAM_MAX_CMD];
    while (1)
    {
        printf("shell> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            break; // Sai se a leitura falhar
        }

        // Remove nova linha
        cmd[strcspn(cmd, "\n")] = 0;

        // Expande variáveis
        char *cmd_expandido = expandir_variaveis(cmd);

        // Verifica se há pipe
        if (strstr(cmd_expandido, "|") != NULL)
        {
            char *cmd1 = strtok(cmd_expandido, "|");
            char *cmd2 = strtok(NULL, "|");
            executar_pipe(cmd1, cmd2);
        }
        else
        {
            executar_comando(cmd_expandido);
        }

        free(cmd_expandido); // Libera a memória do comando expandido
    }

    return 0;
}

void executar_comando(char *cmd)
{
    char prog_c[TAM_CAMINHO], prog_bin[TAM_CAMINHO];
    struct stat stat_c, stat_bin;

    // Monta os nomes do arquivo C e do binário
    snprintf(prog_c, sizeof(prog_c), "%s.c", cmd);
    snprintf(prog_bin, sizeof(prog_bin), "%s", cmd);

    // Verifica se o arquivo C existe
    if (stat(prog_c, &stat_c) == 0)
    {
        // O arquivo C existe, agora verifica se o binário existe
        if (stat(prog_bin, &stat_bin) != 0 || stat_c.st_mtime > stat_bin.st_mtime)
        {
            // Se o binário não existe ou o arquivo C é mais recente, compila
            printf("Compilando %s...\n", prog_c);
            pid_t pid = fork();
            if (pid == 0)
            {
                // Processo filho compila o programa
                execlp("gcc", "gcc", prog_c, "-o", prog_bin, NULL);
                printf("Falha ao compilar %s\n", prog_c);
                exit(1);
            }
            else if (pid > 0)
            {
                wait(NULL); // Espera a compilação terminar
            }
            else
            {
                perror("fork");
                return;
            }
        }

        // Executa o binário
        printf("Executando %s...\n", prog_bin);
        pid_t pid = fork();
        if (pid == 0)
        {
            execlp(prog_bin, prog_bin, NULL);
            printf("Erro ao executar %s\n", prog_bin);
            exit(1);
        }
        else if (pid > 0)
        {
            wait(NULL); // Espera o programa terminar
        }
        else
        {
            perror("fork");
        }
    }
    else
    {
        // Verifica se o formato é VARIÁVEL=/caminho
        if (strstr(cmd, "=") != NULL)
        {
            char *nome = strtok(cmd, "=");
            char *valor = strtok(NULL, "=");
            if (valor != NULL)
            {
                definir_variavel_caminho(nome, valor); // Define o valor da variável
            }
        }
        else if (strcmp(cmd, "CAMINHO") == 0)
        {
            imprimir_variavel_caminho("CAMINHO");
        }
        else if (var_caminho != NULL && strcmp(cmd, var_caminho) == 0)
        {
            // Se o comando é exatamente o valor de CAMINHO, apenas imprime
            printf("%s\n", var_caminho);
        }
        else
        {
            // Comando externo ou outros internos
            char *args[TAM_MAX_ARG];
            char *token = strtok(cmd, " ");
            int i = 0;

            while (token != NULL && i < TAM_MAX_ARG - 1)
            {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            if (strcmp(args[0], "cd") == 0)
            {
                mudar_diretorio(args[1]);
            }
            else if (strcmp(args[0], "pwd") == 0)
            {
                imprimir_diretorio_atual();
            }
            else
            {
                pid_t pid = fork();
                if (pid == 0)
                {
                    // Processo filho
                    execvp(args[0], args);
                    printf("comando não encontrado\n");
                    exit(1);
                }
                else if (pid > 0)
                {
                    // Processo pai espera o filho
                    wait(NULL);
                }
                else
                {
                    perror("fork");
                }
            }
        }
    }
}

void definir_variavel_caminho(char *nome, char *novo_caminho)
{
    if (strcmp(nome, "CAMINHO") == 0)
    {
        if (var_caminho != NULL)
        {
            free(var_caminho);
        }
        var_caminho = strdup(novo_caminho); // Armazena o novo caminho na variável
    }
}

void imprimir_variavel_caminho(char *nome)
{
    if (strcmp(nome, "CAMINHO") == 0 && var_caminho != NULL)
    {
        printf("%s\n", var_caminho);
    }
}

void mudar_diretorio(char *caminho)
{
    if (chdir(caminho) != 0)
    {
        perror("chdir");
    }
}

void imprimir_diretorio_atual()
{
    char cwd[TAM_CAMINHO];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("getcwd");
    }
}

char *expandir_variaveis(char *cmd)
{
    char *result = malloc(TAM_MAX_CMD);
    strcpy(result, cmd);

    // Procurar pela variável $CAMINHO
    char *pos = strstr(result, "$CAMINHO");
    if (pos != NULL && var_caminho != NULL)
    {
        // Calcula novo tamanho do comando após a substituição
        int tamanho_novo_cmd = strlen(result) - strlen("$CAMINHO") + strlen(var_caminho);
        char *cmd_expandido = malloc(tamanho_novo_cmd + 1);

        // Copia a parte antes de $CAMINHO
        strncpy(cmd_expandido, result, pos - result);
        cmd_expandido[pos - result] = '\0';

        // Concatena o valor de CAMINHO
        strcat(cmd_expandido, var_caminho);

        // Concatena a parte após $CAMINHO
        strcat(cmd_expandido, pos + strlen("$CAMINHO"));

        free(result);           // Libera a memória do comando anterior
        result = cmd_expandido; // Atualiza o comando expandido
    }

    return result;
}

void executar_pipe(char *cmd1, char *cmd2)
{
    int fd[2];
    pipe(fd);

    if (fork() == 0)
    {
        // Primeiro filho
        dup2(fd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
        close(fd[0]);
        close(fd[1]);
        executar_comando(cmd1);
        exit(0);
    }

    if (fork() == 0)
    {
        // Segundo filho
        dup2(fd[0], STDIN_FILENO); // Redireciona a entrada para o pipe
        close(fd[0]);
        close(fd[1]);
        executar_comando(cmd2);
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}