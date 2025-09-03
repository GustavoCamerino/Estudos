/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.4
 * @date 2022-02-04
 * 
 */

// Inclusao do cabecalho
#include "synt.h"

// Variaveis globais
type_token *lookahead;
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
extern char output_file_name[MAX_CHAR];
extern FILE *output_file;

/**
 * @brief Verifica se o proximo caracter (a frente) na cadeia eh o esperado
 * 
 * @param token_tag (int) codigo do token a ser verificado 
 * @return int true/false
 */
int match(int token_tag) {
    if ( lookahead->tag == token_tag ) {
        lookahead = getToken(); //Pega o proximo token por meio do lexico
        return true;
    }
    printf("[ERRO] Entrada esperada: %s\n", lookahead->lexema);
    return false;
}

/**
 * @brief Regra de derivacao inicial
 */
int program(void) {
    return declarations();
    //statements();  // Por enquanto nao processa comandos     
}

/**
 * @brief Regra de derivacao para declaracoes
 */
int declarations(void) {
    int result;

    do {
        result = declaration(); // Processa uma declaração
        if (result == ERROR) {
            return false; // Retorna falso em caso de erro
        }
    } while (result == true); // Continua enquanto houver declarações

    return true;
}


/**
 * @brief Regra de derivacao declaracao
 * @return int true/false
 */
int declaration (void) {
    type_symbol_table_entry *search_symbol;
    int ok1, ok2;
    char var_name[MAX_CHAR];
    int var_type;  // Armazena o tipo

    // Verifica se a tag eh de um tipo INTEIRO ou FLOAT
    if (lookahead->tag == FLOAT || lookahead->tag == INT) { 
        var_type = lookahead->tag;  // Armazena o tipo (INT ou FLOAT)
        match(lookahead->tag); // Consome o tipo (INT ou FLOAT)

        // Salva o nome da variavel
        strcpy(var_name, lookahead->lexema);
        
        // Antes de declarar a variavel, verifica se ela ja foi declarada
        search_symbol = sym_find(var_name, &global_symbol_table_variables);
        
        // Se a variavel ja foi declarada, retorna erro
        if (search_symbol != NULL) {
            printf("[ERRO] Variavel '%s' ja declarada.\n", var_name); 
            return ERROR;
        } 

        // Registra a variavel
        if (!match(ID)) {  // Se ok1 for falso, imprime o erro e retorna erro
            printf("[ERRO] Identificador esperado, mas encontrou: %s\n", lookahead->lexema);
            return ERROR;
        }

        // Verifica o ponto e virgula
        if (!match(SEMICOLON)) {  // Se ok2 for falso, imprime o erro e retorna erro
            printf("[ERRO] Ponto e virgula esperado, mas encontrou: %s\n", lookahead->lexema);
            return ERROR;
        }

        // Registra a variavel apenas se nao tiver erros
        sym_declare(var_name, var_type, 0, &global_symbol_table_variables);

        // Se tudo der certo, retorna true
        return true;


    } else if (lookahead ->tag == ENDTOKEN ) {
        // Verifica se fim de arquivo
        return false;         

    } else {
        printf ("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return ERROR; 
    }
}

/**
 * @brief Regra de derivacao para comandos
 */
int statements (void) {
    while (true) {
        if (!statement()) {
            return false;  // Retorna false
        }
    }
    return true;  // Caso seja bem-sucedidos
}

/**
 * @brief Regra de derivacao que processa um comando
 * 
 * @return int true/false
 */
int statement (void) {
    return false;
}




//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 * 
 * @return int 
 */
int main(int argc, char *argv[]) {

    //Inicializa a tabela de simbolo global
    initSymbolTableVariables(&global_symbol_table_variables);
    initSymbolTableString();

    //Verifica a passagem de parametro
    if (argc != 2) {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }
    
    initLex(argv[1]); //Carrega codigo
    lookahead = getToken(); //Inicializacao do lookahead
    
    int sucess = program(); //Chamada da derivacao/funcao inicial da gramatica

    if (sucess != true) {
        printf("ERRO\n");
    
    } else {
        printSTVariables(&global_symbol_table_variables);

        strcpy(output_file_name, argv[1]);
        strcat(output_file_name, ".asm");
        output_file = fopen(output_file_name, "w+");
        gen_data_section(); //Gera codigo da secao de dados
        fclose(output_file);
    }

    return 1;
}