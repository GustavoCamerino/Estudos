#include <stdio.h>    // Para printf, perror
#include <stdlib.h>   // Para exit
#include <fcntl.h>    // Para open e suas flags
#include <unistd.h>   // Para fork, write, close, sleep
#include <string.h>   // Para strlen
#include <sys/wait.h> // Para wait

int main()
{
    const char *nome_arquivo = "arquivo_concorrente.txt";
    int fd; // Descritor de arquivo

    // 1. Abre/Cria o arquivo no processo pai ANTES do fork
    // O_CREAT: Cria se não existir
    // O_WRONLY: Abre para escrita
    // O_TRUNC: Trunca para 0 se existir (esvazia)
    // 0644: Permissões de leitura/escrita para o dono, leitura para grupo/outros
    fd = open(nome_arquivo, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("Pai: Erro ao abrir/criar o arquivo");
        exit(EXIT_FAILURE);
    }
    printf("Pai (PID: %d): Arquivo '%s' aberto com FD: %d\n", getpid(), nome_arquivo, fd);

    pid_t pid = fork(); // Chama fork()

    if (pid < 0)
    {
        // Erro ao criar o processo filho
        perror("Erro ao chamar fork()");
        close(fd); // Fechar o arquivo mesmo em caso de erro no fork
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Este é o processo filho
        printf("Filho (PID: %d): Descritor de arquivo recebido: %d\n", getpid(), fd);

        // O filho escreve no arquivo
        const char *mensagem_filho = "Mensagem do FILHO (PID: %d).\n";
        char buffer_filho[100];
        sprintf(buffer_filho, mensagem_filho, getpid());

        for (int i = 0; i < 5; ++i)
        {
            ssize_t bytes_escritos = write(fd, buffer_filho, strlen(buffer_filho));
            if (bytes_escritos == -1)
            {
                perror("Filho: Erro ao escrever no arquivo");
                break; // Sai do loop em caso de erro
            }
            printf("Filho (PID: %d): Escreveu %zd bytes.\n", getpid(), bytes_escritos);
            usleep(100000); // Pequena pausa para permitir a concorrência
        }

        printf("Filho (PID: %d): Encerrando.\n", getpid());
        close(fd);          // O filho fecha sua cópia do descritor de arquivo
        exit(EXIT_SUCCESS); // O filho termina
    }
    else
    {
        // Este é o processo pai
        printf("Pai (PID: %d): Descritor de arquivo: %d. Filho criado com PID: %d\n", getpid(), fd, pid);

        // O pai escreve no arquivo
        const char *mensagem_pai = "Mensagem do PAI (PID: %d).\n";
        char buffer_pai[100];
        sprintf(buffer_pai, mensagem_pai, getpid());

        for (int i = 0; i < 5; ++i)
        {
            ssize_t bytes_escritos = write(fd, buffer_pai, strlen(buffer_pai));
            if (bytes_escritos == -1)
            {
                perror("Pai: Erro ao escrever no arquivo");
                break; // Sai do loop em caso de erro
            }
            printf("Pai (PID: %d): Escreveu %zd bytes.\n", getpid(), bytes_escritos);
            usleep(150000); // Pequena pausa, diferente do filho, para variar o agendamento
        }

        // O pai aguarda o filho terminar
        wait(NULL);

        printf("Pai (PID: %d): Filho %d finalizou. Encerrando.\n", getpid(), pid);
        close(fd); // O pai fecha sua cópia do descritor de arquivo
    }

    return 0; // Indica sucesso
}