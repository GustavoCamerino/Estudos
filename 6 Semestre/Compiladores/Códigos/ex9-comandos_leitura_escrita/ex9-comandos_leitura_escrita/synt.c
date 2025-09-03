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
void program (void) {
    declarations();
    gen_data_section(); //Chamada do gerador de codigo para declaracao de variaveis
    gen_preambule_code(); //Chamada do gerador de codigo para escrita do cabecalho da secao de codigo
    statements();
    gen_epilog_code();
}

/**
 * @brief Regra de derivacao para declaracoes
 */
void declarations(void) {
    while ( declaration() ); //Laco para processamento continuo das declaracoes
}

/**
 * @brief Regra de derivacao declaracao
 * @return int true/false
 */
int declaration (void) {
    type_symbol_table_entry *search_symbol;
    int ok1, ok2;
    char var_name[MAX_CHAR];

    //Verifica se a tag eh de um INTEIRO
    if ( lookahead->tag == INT ) { 
        match(INT);
        strcpy(var_name, lookahead->lexema);
        search_symbol = sym_find( var_name, &global_symbol_table_variables );

        if ( search_symbol != NULL) {
            printf ("[ERRO] Variavel '%s' ja declarada.\n", var_name); 
            return false;
        } else {
            sym_declare( var_name, INT, 0, &global_symbol_table_variables);
            ok1 = match(ID); //Verifica se identificador vem a seguir
            ok2 = match(SEMICOLON); //Verifica se ; vem a seguir
            return ok1 && ok2;
        }
    } else if (lookahead->tag == ENDTOKEN ||
                lookahead->tag == READ ||
                lookahead->tag == WRITE) {
        //Verifica se fim de arquivo
        return false;         
    } else {
        printf ("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return false; 
    }
}

/**
 * @brief Regra de derivacao para comandos
 */
void statements (void) {
   while ( statement() );  //processa enquanto houver comandos
}

/**
 * @brief Regra de derivacao que processa os comandos
 * 
 * @return int true/false
 */
int statement (void) {
    char lexeme_of_id[MAX_CHAR];

    if (lookahead->tag == READ) {
        match(READ);
        strcpy(lexeme_of_id, lookahead->lexema);
        match(ID);
        gen_read(lexeme_of_id);
        match(SEMICOLON);
        return true;
    } else if (lookahead->tag == WRITE) {
        match(WRITE);
        strcpy(lexeme_of_id, lookahead->lexema);
        match(ID);
        gen_write(lexeme_of_id);
        match(SEMICOLON);
        return true;
    } else if (lookahead->tag == ENDTOKEN) {
        return false;
    } else {
        printf("[ERRO] Comando desconhecido.\n");
        return false;
    }
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

    //Abre o arquivo de saida 
    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, ".asm");
    output_file = fopen(output_file_name, "w+");

    gen_preambule(); //Temporariamente cria um preambulo adicional que permite o uso das funcoes scanf e printf
    program(); //Chamada da derivacao/funcao inicial da gramatica

    fclose(output_file);
    return 1;
}