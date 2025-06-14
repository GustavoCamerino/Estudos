/**
 * @file novo_shell.c
 * @date 18/09/2023
 * Sistemas Operacionais 1\n
 * Prof. Maxwell\n
 *
 * @brief Programa que implementa um shell (baseado no linux) na linguagem "C", de acordo com os requisitos passados em aula
 * @author Gabriel Neves Silveira
 * @version 1.0
 */

// Bibliotecas
#include <stdio.h>    // Biblioteca Padrao de entrada e saida
#include <stdlib.h>   // Biblioteca de utilitarios relacionados a alocacao de memoria (malloc, free...)
#include <string.h>   // Biblioteca de manipulacao de strings
#include <unistd.h>   // Biblioteca de constantes, tipos simbolicos e funcoes variadas (exec, pipe...)
#include <sys/wait.h> // Biblioteca com funcoes de espera (wait ())
#include <sys/stat.h> // Biblioteca para manipular data de modificacao de arquivos
#include <signal.h>   // Biblioteca com funcoes de tratamento de sinais

// Prototipos
int compara_tempos(char *caminho_arq_c, char *caminho_arq_bin);
void compila_sem_perror(char *arquivo, char *arquivo_bin);
void roda_pipe(char *programa_completo);
void roda_c_e_background(char *programa_completo, int imprime_perror);
void filho_finalizou();
void finaliza_tudo();

/**
 * @brief Funcao principal do programa_completo
 * @return "0" Caso o programa_completo finalize com sucesso
 * @return Qualquer outra coisa caso o programa_completo finalize com alguma falha
 */
int main(int argc, char *argv[])
{
    char comando[1000]; // Recebe os comandos do usuario

    // Inicialmente coloca a variavel de ambiente "Caminho" (PATH) como sendo a pasta do arquivo do shell
    setenv("PATH", getcwd(comando, 100), 1);

    // Caso os argumentos tenham tamanho errado eh dado um erro
    if ((argc > 1) && ((strcmp(argv[1], "export")) != 0))
    {
        printf("Uso: %s <export> <CAMINHO=/pasta:/pasta...>\n", argv[0]);
        return -1;
    }

    // Caso os argumentos estejam do tamanho certo
    if (argc == 3)
    {
        char *caminho = argv[2] + 8; // Recebe o endereco do caminho

        // Verifica se o "CAMINHO=/<endereco...>" estah correto
        if ((strncmp(argv[2], "CAMINHO=", 7) == 0) && (*caminho == '/'))
        {
            setenv("PATH", caminho, 1); // Se tiver correto seta a variavel de ambiente caminho (PATH)
        }
        else
        { // Caso esteja incorreto eh dado um erro
            printf("Uso: %s <export> <CAMINHO=/pasta:/pasta...>\n", argv[0]);
            return -1;
        }
    }

    // Looping infinito ateh o usuario finalizar o shell com o comando "exit"
    do
    {
        filho_finalizou(); // Funcao verifica se algum comando em background finalizou para pode derrubar o processo

        printf("%s: >>> ", getenv("USER"));     // Nome do usuario e simbolo que aparece antes do usuario digitar algo (prompt)
        fgets(comando, sizeof(comando), stdin); // Le o que o usuario digitou e passa para o comando
        comando[strcspn(comando, "\n")] = 0;    // Remove o '\n' do final do comando

        // Caso o usario de o comando Ctrl + Z ou CTRL + c, finaliza todos os processos que estejam em pe
        signal(SIGTSTP, finaliza_tudo);
        signal(SIGINT, finaliza_tudo);

        // Usuario digitou comando 'cd'
        if (comando[0] == 'c' && comando[1] == 'd')
        {
            int error;                 // Recebe o retorno do "chdir"
            char *pasta = &comando[3]; // Aponta para a pasta do comando 'cd'

            error = chdir(pasta); // Vai para o diretorio indicado na pasta

            // Caso o diretorio digitado esteja incorreto
            if (error == -1)
            {
                perror("Diretorio nao encontrado");
            }

            // Usuario digitou comando 'pwd'
        }
        else if (comando[0] == 'p' && comando[1] == 'w' && comando[2] == 'd')
        {
            char pasta_atual[300];                    // Recebe a pasta atual onde o shell estah
            printf("%s\n", getcwd(pasta_atual, 300)); // Printa a pasta autal do shell

            /*
                Usuario digitou comando para rodar programa (programa localizado em CAMINHO ou programa em c)
                So entra no else caso o usuario digite alguma coisa
            */
        }
        else if ((strcmp(comando, "exit") != 0) && (comando[0] != 0) && (comando[0] != 32) && (comando[0] != 9))
        {
            int id = fork(), status; // Cria um processo

            // Caso o processo o processo de algum erro
            if (id < 0)
            {
                printf("Erro ao criar processo\n");
                exit(EXIT_FAILURE);
            }

            if (id == 0)
            {
                // Processo filho
                char *programa_completo = strtok(comando, " "); // Recebe o comando divido em tokens
                char *args[100];                                // Recebe os argumentos do "programa_completo"
                char arquivo[100], arquivo_bin[100];            // Verifica se existe arquivo C e binario (do arquivo C)
                int i = 0, existe_arq = 0;

                // Faz um looping em cada argumento do comando, armazenando os valores no vetor "args"
                while (programa_completo != NULL)
                {

                    // Verifica se o usuario pediu pra rodar com pipe
                    if (strcmp(programa_completo, "|") == 0)
                    {
                        char arquivo_1[100], arquivo_1_bin[100], arquivo_2[100], arquivo_2_bin[100];
                        int existe_arq1 = 0, existe_arq2 = 0;

                        // Cria um vetor de char com o programa em C e o programa binario (compilado)
                        strcpy(arquivo_1, args[0]);
                        strcat(arquivo_1, ".c");
                        strcpy(arquivo_1_bin, args[0]);

                        // Verifica se o que o usuario escreveu eh um programa
                        existe_arq1 = compara_tempos(arquivo_1, arquivo_1_bin);
                        compila_sem_perror(arquivo_1, arquivo_1_bin);
                        wait(NULL); // Espera o processo da funcao acima terminar

                        programa_completo = strtok(NULL, " "); // Pula para o proximo comando (posterior ao pipe)

                        // Caso exista algum comando apos o pipe
                        if (programa_completo != NULL)
                        {
                            // Cria um vetor de char com o programa em C e o programa binario (compilado)
                            strcpy(arquivo_2, programa_completo);
                            strcat(arquivo_2, ".c");
                            strcpy(arquivo_2_bin, programa_completo);

                            // Verifica se o que o usuario escreveu eh um programa
                            existe_arq2 = compara_tempos(arquivo_2, arquivo_2_bin);
                            compila_sem_perror(arquivo_2, arquivo_2_bin);
                            wait(NULL); // Espera o processo da funcao acima terminar
                        }

                        exit(0); // No final, compilando ou nao o filho sai
                    }

                    // Verifica se o usuario pediu pra rodar em background
                    if (strcmp(programa_completo, "&") == 0)
                    {
                        break; // Sai do looping, tira o simbolo de background e roda o programa
                    }

                    // Preenche os argumentos
                    args[i] = programa_completo;
                    programa_completo = strtok(NULL, " ");
                    i++;
                }
                args[i] = NULL; // Ultima posicao dos argumentos recebe NULL

                // Cria um vetor de char com o programa em C e o programa binario (compilado)
                strcpy(arquivo, args[0]);
                strcat(arquivo, ".c");
                strcpy(arquivo_bin, args[0]);

                // Verifica se eh programa ou arquivo em C
                existe_arq = compara_tempos(arquivo, arquivo_bin);

                // Caso seja um programa
                if (existe_arq == -1)
                {
                    // Executa o programa
                    execvp(args[0], args);

                    // Caso ocorra um erro
                    perror("Comando nao encontrado");
                    exit(-1);

                    // Caso seja um arquivo C
                }
                else
                {

                    // Compila o programa caso nao tenha binario ou a data entre programa e binario sejam diferentes
                    if (existe_arq == 1)
                    {
                        execlp("gcc", "gcc", arquivo, "-o", arquivo_bin, NULL);

                        // Caso ocorra um erro
                        perror("Comando nao encontrado");
                        exit(-1);
                    }

                    exit(0); // Caso nao exista arquivo C ou nao precise ser compilado (tem a mesma data)
                }
            }
            else
            {
                // Processo pai

                // Se nao for background, espera o filho terminar
                if (strchr(comando, '&') == NULL)
                {
                    wait(&status); // Espera o filho acabar e pega o seu estado

                    // Se o filho terminar corretamente
                    if ((WIFEXITED(status)) && ((WEXITSTATUS(status)) == 0))
                    {

                        // Se for pipe
                        if (strchr(comando, '|') != NULL)
                        {
                            char *programa_completo = strtok(comando, " "); // Transforma os comandos em tokens

                            // Chama a funcao para rodar o comando
                            roda_pipe(programa_completo); // Os erros sao impressos dentro da funcao

                            // Comando eh um programa em C
                        }
                        else
                        {
                            char *programa_completo = strtok(comando, " "); // Divide o comando em tokens
                            char programa[100] = {"./"}, programa_c[100];   // Recebem o primeiro arugmento
                            int existe_arq = 0;

                            // Pega o primeiro argumento e passa para vetores char, sendo o arquivo em C e o binario
                            strcat(programa, programa_completo);
                            strcpy(programa_c, programa_completo);
                            strcat(programa_c, ".c");

                            existe_arq = compara_tempos(programa_c, programa); // Verifica se o comando eh um arquivo em C

                            // Caso de um erro e seja um arquivo em C (nao seja um programa)
                            if (existe_arq != -1)
                            {
                                // Chama a funcao para rodar o comando (podendo imprimir perror)
                                roda_c_e_background(programa_completo, 1);

                                wait(NULL); // Epera o processo terminar
                            }
                        }
                    }
                }
                else
                {
                    // Caso seja background, tenta rodar o comando como se fosse um programa
                    comando[strlen(comando) - 1] = 0;               // Remove o simbolo "&" do comando
                    char *programa_completo = strtok(comando, " "); // Divide o comando em tokens

                    // Chama a funcao para rodar o comando
                    roda_c_e_background(programa_completo, 0);
                }
            }
        }

        filho_finalizou(); // Verifica a cada looping se existe um processo zumbi

    } while (strcmp(comando, "exit") != 0);

    // Caso o usario digite exit todos os processos (que ainda nao foram) sao finalizados
    atexit(finaliza_tudo);

    return 0;
}

// Funcoes e Procedimentos

/**
 * @brief Funcao que compara o tempo entre dois arquivos, um em C e o seu binario (compilado)
 * @param caminho_arq_c Caminho onde estah localizado o arquivo em C
 * @param caminho_arq_bin Caminho onde estah localizado o arquivo binario
 * @return "1" Caso o arquivo binario nao exista, ou o arquivo em C e o binario tenham tempo de modificacao diferentes
 * @return "0" Caso o arquivo em C e o binario tenham tempo de modificacao iguais (nao precisa compilar)
 * @return "-1" Caso nao exista um arquivo em C
 */
int compara_tempos(char *caminho_arq_c, char *caminho_arq_bin)
{
    struct stat arquivo1_c, arquivo1_bin; // Recebem o caminho dos arquivos

    // Caso exista o arquivo em C
    if (stat(caminho_arq_c, &arquivo1_c) == 0)
    {

        // Se o arquivo binario existir
        if (stat(caminho_arq_bin, &arquivo1_bin) == 0)
        {
            // Compara o tempo de modificacao do arquivo em C e o binario

            if (arquivo1_c.st_mtime > arquivo1_bin.st_mtime)
            {
                return 1; // O arquivo em C foi modificado (tempo eh maior que o binario)
            }
            else
            {
                return 0; // O arquivo em C nao foi modificado (tempo eh igual)
            }

            // Caso o arquivo binario nao exista
        }
        else
        {
            return 1;
        }
    }

    return -1; // Caso o arquivo em C nao exista na pasta onde o shell estah localizado
}

/**
 * @brief Procedimento que compila um arquivo em C sem dar uma mensagem de erro
 * @details Eh utilizado para compilar arquivos em pipe (caso tenha um arquivo em C)
 * @param arquivo Nome do arquivo em C para ser compilado
 * @param arquivo_bin Nome do aquivo binario do arquivo em C
 */
void compila_sem_perror(char *arquivo, char *arquivo_bin)
{
    int existe_arq = 0;

    // Verifica se o que o usuario escreveu eh um programa
    existe_arq = compara_tempos(arquivo, arquivo_bin);

    int id = fork(); // Cria um processo

    // Caso o processo tenha alguma falha
    if (id == -1)
    {
        perror("Erro ao executar o fork\n");
        exit(EXIT_FAILURE);
    }

    // Verifica se o arquivo a esquerda do pipe eh um programa
    if (id == 0)
    { // Filho

        // Compila o programa caso nao tenha binario ou a data entre programa e binario sejam diferentes
        if (existe_arq == 1)
        {
            execlp("gcc", "gcc", arquivo, "-o", arquivo_bin, NULL);

            exit(-1); // Caso ocorra um erro o filho sai
        }

        exit(0); // Caso nao exista arquivo C ou nao precise ser compilado (tem a mesma data)
    }
}

/**
 * @brief Funcao que roda o comando quando for um pipe
 * @param programa_completo Comando dividido em tokens
 */
void roda_pipe(char *programa_completo)
{
    char *args1[100], *args2[100]; // Recebe os argumentos
    int i = 0;

    // Faz um looping pegando todos os argumentos
    while (programa_completo != NULL)
    {
        // Caso esteja a direita do pipe, sao colocados os argumentos a direita para args2
        if (strcmp(programa_completo, "|") == 0)
        {
            args1[i] = NULL; // Coloca a ultima posicao a esqueda do pipe como NULL

            programa_completo = strtok(NULL, " "); // Ignora o pipe "|" pulando pro proximo argumento
            i = 0;                                 // Reseta o contador

            // Argumentos a direita do pipe
            while (programa_completo != NULL)
            {
                // Atribui os argumentos a direita do pipe
                args2[i] = programa_completo;
                programa_completo = strtok(NULL, " "); // Pula pro proximo argumento
                i++;
            }

            // Caso esteja a esquerda do pipe, sao colocados os argumentos a esquerda para args1
        }
        else
        {
            // Atribui os argumentos a esquerda do pipe
            args1[i] = programa_completo;
            programa_completo = strtok(NULL, " ");
            i++;
        }
    }
    args2[i] = NULL; // Coloca a ultima posicao a direita do pipe como NULL

    int id = fork(); // Cria um processo novo

    // Verifica se o processo abriu corretamente
    if (id == -1)
    {
        perror("Erro ao executar o fork\n");
        exit(EXIT_FAILURE);
    }

    // Filho
    if (id == 0)
    {
        int fd[2]; // fd Recebe os comandos (0 eh um arquivo e 1 eh outro)

        /*
            Transforma fd em um pipe

            [0] = leitura, recebe 1
            [1] = escrita, manda para 0
        */
        pipe(fd);

        int id2 = fork(); // Cria um processo novo (Neto)

        // Verifica se o processo abriu corretamente
        if (id2 == -1)
        {
            perror("Erro ao criar processo\n");
            exit(EXIT_FAILURE);
        }

        // Neto
        if (id2 == 0)
        {
            int error;

            close(fd[0]);               // Fecha o lado da escrita
            dup2(fd[1], STDOUT_FILENO); // Redireciona stdout para o pipe
            close(fd[1]);               // Fecha a leitura no final

            // Executa o programa
            error = execvp(args1[0], args1);

            // Caso o programa tenha dado erro, vai tentar executar um binario
            if (error == -1)
            {
                // Vetor arquivo recebe o executavel "./<nomedoarquivo>"
                char arquivo[100] = {"./"};
                strcat(arquivo, args1[0]);

                args1[0] = args1[1]; // Args1 recebe exclusivamente os argumentos

                // Executa o programa
                execvp(arquivo, args1);

                // Caso de algum erro na execucao (nao eh programa e nem programa em C)
                perror("Comando nao encontrado");
                exit(-1);
            }
        }
        else
        {               // Filho
            wait(NULL); // Espera infinitamente ateh o Neto morrer (evita processo zumbi)
            int error;

            close(fd[1]);              // Fecha lado da leitura
            dup2(fd[0], STDIN_FILENO); // Redireciona stdin para o pipe
            close(fd[0]);              // Fecha a escrita no final

            // Executa o programa
            error = execvp(args2[0], args2);

            // Caso o programa tenha dado erro, vai tentar executar um binario
            if (error == -1)
            {
                // Vetor arquivo recebe o executavel "./<nomedoarquivo>"
                char arquivo[100] = {"./"};
                strcat(arquivo, args2[0]);

                args2[0] = args2[1]; // Args2 recebe exclusivamente os argumentos

                // Executa o binario
                execvp(arquivo, args2);

                // Caso de algum erro na execucao (nao eh programa e nem programa em C)
                perror("Comando nao encontrado");
                exit(-1);
            }
        }
    }

    wait(NULL); // Espera ateh um processo ser finalizado
}

/**
 * @brief Procedimento que roda um programa como um arquivo binario
 * @details Ele eh usado para rodar comando de codigo em C e codigo em C em background
 * @param programa_completo Codigo do programa dividido em tokens
 * @param imprime_perror Flag para imprimir ou nao uma mensagem de erro, recebe "0" para programa em C em background e "1" para programa em C
 */
void roda_c_e_background(char *programa_completo, int imprime_perror)
{
    char programa[100] = {"./"}, programa_c[100]; // Recebem o primeiro arugmento
    char *args[100];                              // Recebe os argumentos
    int i = 0, status;

    // Faz um looping pegando todos os argumentos
    while (programa_completo != NULL)
    {
        // Atribui os argumentos
        args[i] = programa_completo;
        programa_completo = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL; // Coloca a ultima posicao como NULL

    // Pega o primeiro argumento e passa para vetores char, sendo o arquivo em C e o binario
    strcat(programa, args[0]);
    strcpy(programa_c, args[0]);
    strcat(programa_c, ".c");

    int id = fork(); // Criando um filho

    // Caso de erro no processo
    if (id < 0)
    {
        printf("Erro ao criar processo\n");
        exit(EXIT_FAILURE);
    }

    if (id == 0)
    {                      // Filho
        args[0] = args[1]; // Args recebe exclusivamente os argumentos

        // Executa o programa
        execvp(programa, args);

        // Caso de algum erro
        exit(-1);
    }
    else
    {                  // Pai
        wait(&status); // Espera o filho terminar de executar

        // Caso a flag de imprimir esteja habilitada e o comando do filho tenha dado erro
        if ((imprime_perror == 1) && ((WEXITSTATUS(status)) != 0))
        {
            perror("Comando nao econtrado");
        }
    }
}

/**
 * @brief Procedimento que eh utilizado para derrubar processos em background que finalizaram
 */
void filho_finalizou()
{
    // Procura um processo qualquer (e se achar eh finalizado)
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
}

/**
 * @brief Procedimento que eh utilizado quando o programa encerra para finalizar todos os processos vivos
 */
void finaliza_tudo()
{
    // Finaliza todos o grupo de processos criados pelo programa
    kill(0, SIGKILL);
}