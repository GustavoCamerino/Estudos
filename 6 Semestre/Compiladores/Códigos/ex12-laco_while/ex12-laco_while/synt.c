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
int match(int token_tag)
{
    if (lookahead->tag == token_tag)
    {
        lookahead = getToken(); // Pega o proximo token por meio do lexico
        return true;
    }
    printf("[ERRO] Entrada esperada: %s\n", lookahead->lexema);
    return false;
}

/**
 * @brief Regra de derivacao inicial
 */
void program(void)
{
    gen_preambule(); // Temporariamente cria um preambulo adicional que permite o uso das funcoes scanf e printf
    declarations();
    gen_preambule_code(); // Chamada do gerador de codigo para escrita do cabecalho da secao de codigo
    statements();
    gen_epilog_code();
    gen_data_section(); // Chamada do gerador de codigo para declaracao de variaveis
}

/**
 * @brief Regra de derivacao para declaracoes
 */
void declarations(void)
{
    while (declaration()); // Laco para processamento continuo das declaracoes
    //DEBUG
    //Imprime tabela de funcoes e variaveis
    
}


/**
 * @brief Regra de derivacao declaracao
 * @return int true/false
 */
int declaration(void)
{
    type_symbol_table_entry *search_symbol;
    int ok1, ok2;
    char var_name[MAX_CHAR];
    int var_type;

    // Verifica o tipo da variavel
    var_type = lookahead->tag;
    if (var_type == INT || var_type == FLOAT || var_type == CHAR || var_type == STRING)
    {
        match(var_type);
        strcpy(var_name, lookahead->lexema);
        search_symbol = sym_find(var_name, &global_symbol_table_variables);

        if (search_symbol != NULL)
        {
            printf("[ERRO] Variavel '%s' ja declarada.\n", var_name);
            return false;
        }
        else
        {
            sym_declare(var_name, var_type, 0, &global_symbol_table_variables);
            ok1 = match(ID);        // Verifica se identificador vem a seguir
            ok2 = match(SEMICOLON); // Verifica se ; vem a seguir
            return ok1 && ok2;
        }
    }
    else if (lookahead->tag == ENDTOKEN ||
             lookahead->tag == READ ||
             lookahead->tag == WRITE)
    {
        // Verifica se fim de arquivo
        return false;
    }
    else
    {
        printf("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return false;
    }
}

/**
 * @brief Regra de derivacao para comandos
 */
void statements(void)
{
    while (statement())
        ; // processa enquanto houver comandos
}

/**
 * @brief Regra de derivacao que processa os comandos
 *
 * @return int true/false
 */
int statement(void)
{
    char lexeme_of_id[MAX_CHAR];
    type_symbol_table_entry *search_symbol;
    type_symbol_table_string_entry *gen_string;
    int ok1, ok2, type;
    char string_value[MAX_CHAR];

    if (lookahead->tag == READ)
    {
        match(READ);
        strcpy(lexeme_of_id, lookahead->lexema);
        ok1 = match(ID);
        search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
        if (search_symbol != NULL)
        {
            type = search_symbol->type;
            gen_read(lexeme_of_id, type);
            ok2 = match(SEMICOLON);
            return ok1 && ok2;
        }
        else
        {
            printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
            return false;
        }
    }
    else if (lookahead->tag == WRITE)
    {
        match(WRITE);
        if (lookahead->tag == STRING)
        {
            strcpy(string_value, lookahead->lexema);
            // TODO: verificar se o valor da constante ja foi incluida na tabela de simbolos
            gen_string = sym_string_declare(string_value);
            match(STRING);
            if (gen_string != NULL)
            {
                strcpy(lexeme_of_id, gen_string->name);
                gen_write(lexeme_of_id, STRING);
                match(SEMICOLON);
            }
        }
        else if (lookahead->tag == ID)
        {
            char lexema_of_id[MAX_CHAR];
            type_symbol_table_entry *search_symbol;

            strcpy(lexema_of_id, lookahead->lexema);
            search_symbol = sym_find(lexema_of_id, &global_symbol_table_variables);
            if (search_symbol == NULL)
            {
                printf("[ERRO] Variavel nao declarada: %s\n", lexema_of_id);
                return false;
            }
            match(ID);
            if (lookahead->tag == ASSIGN)
            {
                match(ASSIGN);
                E();                                           // Evaluate the expression, result is on stack
                gen_assign(lexema_of_id, search_symbol->type); // New function to store result
                return match(SEMICOLON);
            }
            else
            {
                printf("[ERRO] Esperado '=' apos identificador: %s\n", lexema_of_id);
                return false;
            }
        }
    }
    else if (lookahead->tag == IF)
    {
        char label_else[MAX_CHAR];
        char label_end[MAX_CHAR];
        gen_label_name(label_else);
        gen_label_name(label_end);

        match(IF);
        match(OPEN_PAR);
        E(); // Expressao booleana
        gen_cond_jump(label_else);
        match(CLOSE_PAR);

        match(BEGIN);
        statements();
        match(END);

        gen_incond_jump(label_end);
        gen_label(label_else);

        // Verifica se ocorre um ELSE
        if (lookahead->tag == ELSE)
        {
            match(ELSE);
            match(BEGIN);
            statements();
            match(END);
        }
        gen_label(label_end);
        return true;
    }
    // While

    else if (lookahead->tag == WHILE)
    {
        char label_start[MAX_CHAR];
        char label_end[MAX_CHAR];
        gen_label_name(label_start);
        gen_label_name(label_end);

        match(WHILE);

        // Verifica abertura de parênteses
        if (match(OPEN_PAR) != 0)
        {
            printf("[ERRO] Esperava-se '(' depois do comando while\n");
            return false;
        }

        gen_label(label_start);

        // booleano
        if (B() != 0)
        {
            printf("[ERRO] Condição dentro do comando while invalida\n");
            return false;
        }

        // Jump condicional para o final do loop
        gen_cond_jump(label_end);

        if (match(CLOSE_PAR) != 0)
        {
            printf("[ERRO] Esperava-se '(' depois do comando while\n");
            return false;
        }

        if (match(BEGIN) != 0)
        {
            printf("[ERRO] Esperava-se comando begin depois do while\n");
            return false;
        }

        // Processa comandos do loop
        statements();

        // Verifica fechamento do bloco 'end'
        if (match(END) != 0)
        {
            printf("[ERRO] Esperava-se comando end no fim do comando while\n");
            return false;
        }

        // Jump incondicional de volta pro início
        gen_incond_jump(label_start);

        gen_label(label_end);

        return true; // Tudo certo
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        return false;
    }
    else
    {
        printf("[ERRO] Comando desconhecido.\nTag=%d; Lexema=%s\n", lookahead->tag, lookahead->lexema);
        return false;
    }
}

/**
 * @brief Regra de derivação que analiza expressoes booleanas
 *        no padrao 'id op_rel expr'
 *
 */
////// TODO
int B()
{
    char lexema_of_id[MAX_CHAR];
    int operator;
    type_symbol_table_entry *search_symbol;

    strcpy(lexema_of_id, lookahead->lexema);
    search_symbol = sym_find(lexema_of_id, &global_symbol_table_variables);
    if (search_symbol == NULL)
    {
        printf("[ERRO] Variavel nao declarada: %s\n", lexema_of_id);
        return false;
    }
    match(ID);
    if (boolOperator(&operator))
    {
        E();
        gen_bool(operator);
        return true;
    }
    else
    {
        return false;
    }
}

int boolOperator(int *operator)
{
    int lookahead_tag;
    lookahead_tag = lookahead->tag;
    *operator= - 1;

    if (lookahead_tag == EQUAL ||
        lookahead_tag == NE ||
        lookahead_tag == LT ||
        lookahead_tag == GT ||
        lookahead_tag == LE ||
        lookahead_tag == GE)
    {
        *operator= lookahead_tag;
        match(lookahead_tag);
        return true;
    }
    else
    {
        printf("[ERRO] Operador relacional experado.\n");
        return false;
    }
}

//------
/* Funções que representam a gramatica que reconhece expressoes aritmeticas */
/* Elaborada nas primeiras aulas */
int E()
{
    int b1, b2;
    b1 = T();
    if (b1)
        b2 = ER();
    return b1 && b2;
}

int ER()
{
    if (lookahead->tag == '+')
    {
        int b1, b2;
        match('+');
        b1 = T();
        genAdd();
        if (b1)
            b2 = ER();
        return b1 && b2;
    }
    else if (lookahead->tag == '-')
    {
        int b1, b2;
        match('-');
        b1 = T();
        genSub();
        if (b1)
            b2 = ER();
        return b1 && b2;
    }
    else if (lookahead->tag == ')')
    {
        return true;
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        return true;
    }
    else if (lookahead->tag == '*')
    {
        return true;
    }
    else if (lookahead->tag == '/')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int T()
{
    int b1, b2;
    b1 = F();
    if (b1)
        b2 = TR();
    return b1 && b2;
}

int TR()
{
    if (lookahead->tag == '*')
    {
        int b1, b2;
        match('*');
        b1 = F();
        genMult();
        if (b1)
            b2 = TR();
        return b1 && b2;
    }
    else if (lookahead->tag == '/')
    {
        int b1, b2;
        match('/');
        b1 = F();
        genDiv();
        if (b1)
            b2 = TR();
        return b1 && b2;
    }
    else if (lookahead->tag == ')')
    {
        return true;
    }
    else if (lookahead->tag == ENDTOKEN)
    { // EOF
        return true;
    }
    else if (lookahead->tag == '+')
    {
        return true;
    }
    else if (lookahead->tag == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int F()
{
    if (lookahead->tag == '(')
    {
        int b1, b2;
        match('(');
        b1 = E();
        if (b1)
            b2 = match(')');
        return b1 && b2;
    }
    else if (lookahead->tag == NUM)
    {
        int b1;
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        b1 = match(NUM); // substituir 'id' por NUM
        genNum(lexema);
        return b1;
    }
    else
    {
        return false;
    }
}
/*fim da importação */
//------

//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 *
 * @return int
 */
int main(int argc, char *argv[])
{

    // Inicializa a tabela de simbolo global
    initSymbolTableVariables(&global_symbol_table_variables);
    initSymbolTableString();

    // Verifica a passagem de parametro
    if (argc != 2)
    {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }

    initLex(argv[1]);       // Carrega codigo
    lookahead = getToken(); // Inicializacao do lookahead

    // Abre o arquivo de saida
    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, ".asm");
    output_file = fopen(output_file_name, "w+");

    program(); // Chamada da derivacao/funcao inicial da gramatica

    fclose(output_file);
    return 1;
}