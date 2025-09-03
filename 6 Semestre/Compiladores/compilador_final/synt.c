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
extern FloatConstant float_constants[MAX_FLOAT];
extern int float_const_count;

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
 * @brief Regra de derivacao inicial 'Programa'
 */ 
void program (void) {
    gen_preambule(); // Cria um preambulo adicional que permite o uso das funcoes scanf e printf
    gen_preambule_code(); // Chamada do gerador de codigo para escrita do cabecalho da secao de codigo

    // Regra de derivacao "Declaracoes"
    declarations(); // Trata as declaracoes de variaveis/funcoes

    // Inicio do bloco principal:
    // Consome 'begin'
    if (!match(BEGIN)) {
        printf("[ERRO] Esperado comando 'begin' antes dos comandos principais\n");
    }
     
    statements(); // Comandos principais (Regra de derivacao "Comandos")

    // Consome 'end'
    if (!match(END)) {
        printf("[ERRO] Esperado comando 'end' depois dos comandos principais\n");
    }

    // Fim do bloco principal
    
    gen_jump_exit(); // Adiciona um jump para o final do bloco begin/end principal (evita rodar as funcoes sem serem chamadas na main)

    // Trata a implementacao das funcoes
    function_statements(); // Equivalente a regra de derivacao "Func_code" da gramatica
    
    gen_epilog_code(); // Gerador de codigo para o fim do programa
    gen_data_section(); // Chamada do gerador de codigo para declaracao de variaveis globais

    // Para DEBUG:
    printf("\n------------------------------------------------------\nDEBUG:\n"); 
    printSTVariables(&global_symbol_table_variables); // Imprime a tabele de variaveis
    printf("\n");
    printSTString(); // Imprime a tabele de Strings
    printf("\n");
    printSTFunctions(); // Imprime a tabela de funcoes (DEBUG)
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
    type_symbol_table_entry *search_var;
    type_symbol_function_entry *search_func;
    int ok1, ok2;
    char name[MAX_CHAR];
    int type;
    
    // Verifica o tipo da variavel
    type = lookahead->tag;
    if ( type == INT || type == FLOAT || type == CHAR || type == STRING) { 
        match(type); // consome o tipo
        strcpy(name, lookahead->lexema); // Pega o nome
        ok1 = match(ID); // Consome o ID
        // Verifica se eh uma funcao (se o proximo token eh '(')
        if (lookahead->tag == '(') {
            match('('); // Consome "("

            // Verifica se a funcao ja foi declarada
            search_func = sym_func_find(name);
            if (search_func != NULL) {
                printf("[ERRO] Funcao '%s' ja declarada.\n", name);
                return false;
            }

            // Variaveis para guardar os parametros e a qtd de parametros
            type_symbol_table_entry params[MAX_PARAMS];
            int nparams = 0;

            // Processa os parametros (se tiver algum)
            while (lookahead->tag == INT || lookahead->tag == FLOAT || 
                    lookahead->tag == CHAR || lookahead->tag == STRING) {
                
                // Pega o tipo do parametro
                int param_type = lookahead->tag;
                match(param_type); // Consome o tipo
                
                
                // Pega o ome do parametro
                char param_name[MAX_CHAR];
                strcpy(param_name, lookahead->lexema);
                if (!match(ID)) { // Consome o nome
                    printf("[ERRO] Nome de parametro invalido.\n");
                    return false;
                }
                

                // Adiciona na lista de parametros
                params[nparams].type = param_type;
                strncpy(params[nparams].name, param_name, MAX_TOKSZ);
                nparams++;

                // Verifica se tem mais parametros
                if (lookahead->tag == ',') {
                    match(','); // Consome a virgula
                    
                    // Se o proximo token nao for uma nova variavel, retorna erro
                    if (lookahead->tag != INT && lookahead->tag != FLOAT && 
                        lookahead->tag != CHAR && lookahead->tag != STRING) {
                        printf("[ERRO] Esperado um novo parametro apos a virgula ','\n");
                        return false;
                    }

                // Se nao tiver virgula e nao tiver fechado os parametros, retorna erro
                } else if (lookahead->tag != ')') {
                    printf("[ERRO] Esperado virgula apos parametro.\n");
                    return false;
                }
            }
            
            // Consome ")"
            if (!match(')')) {
                printf("[ERRO] ')' esperado apos parametros\n");
                return false;
            }
            
            ok2 = match(SEMICOLON); // Consome ";"
            

            // Adiciona a funcao na Tabela de simbolos de funcoes (TSF)
            if (sym_func_declare(name, type, params, nparams) == NULL) { 
                return false; // Se tiver dado erro na hora de declarar, retorna NULL
            }


            return ok1 && ok2;
        }

        // Se nao for uma funcao, trata como variavel
        else {
            // Verifica se a variavel ja esta declarada
            search_var = sym_find(name, &global_symbol_table_variables);
            if (search_var != NULL) {
                printf("[ERRO] Variavel '%s' ja declarada.\n", name);
                return false;
            }

            // Declara a variavel
            sym_declare(name, type, 0, &global_symbol_table_variables);
            
            // Verifica se existe uma atribuicao na criacao da variavel 
            if (lookahead->tag == ASSIGN) {
                match(ASSIGN); // Consome o simbolo "="

                // Realiza a expressao dentro da atribuicao.
                int expr_type = E();

                // Verifica se deu erro na atribuicao
                if (expr_type == ERROR) {
                    printf("[ERRO] Expressao invalida apos atribuicao '='.\n");
                    return false;
                }
                
                // Verifica se o tipo eh compativel com o tipo da variavel
                if (type != expr_type) {
                    printf("[ERRO] Tipo incompativel na atribuicao de '%s'\n", name);
                    return false;
                }

                // Gera codigo de maquina
                gen_assign(name, type);
            }

            ok2 = match(SEMICOLON); // Verifica se lookahead eh ';'

            // Retorna resultado
            return ok1 && ok2;
        }

    // Agora verifica tokens que nao sao declaracoes (adicionando "if", atribuicao de variavel ("id") e "while")
    } else if (lookahead->tag == IF ||
                lookahead->tag == WHILE ||
                lookahead->tag == ID ||
                lookahead->tag == ENDTOKEN ||
                lookahead->tag == READ ||
                lookahead->tag == WRITE ||
                lookahead->tag == BEGIN) {
        //Verifica se fim de arquivo
        return false;         
    } else {
        printf ("[ERRO] Tipo desconhecido: %d | '%s'.\n", lookahead->tag, lookahead->lexema);
        return false; 
    }
}

/**
 * @brief Regra de derivacao para comandos
 * @details Essa funcao verifica a seguinte estrutura:
 * <begin>
 *  Comandos...
 * <end>
 */
void statements (void) {
    while ( statement() );  // Processa enquanto houver comandos
}

/**
 * @brief Regra de derivacao que processa os comandos
 * 
 * @return int true/false
 */
int statement (void) {
    char lexeme_of_id[MAX_CHAR];
    type_symbol_table_entry *search_symbol;
    type_symbol_table_string_entry *gen_string;
    int ok1, ok2, type;
    char string_value[MAX_CHAR];

    
    if (lookahead->tag == READ) {
        match(READ);
        strcpy(lexeme_of_id, lookahead->lexema);
        ok1 = match(ID);
        search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
        if (search_symbol != NULL) {
            type = search_symbol->type;
            gen_read(lexeme_of_id, type);
            ok2 = match(SEMICOLON);
            return ok1 && ok2;
        } else {
            printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
            return false;
        }
    } else if (lookahead->tag == WRITE) {

        match(WRITE);
        if ( lookahead->tag == STRING ) {
            strcpy(string_value, lookahead->lexema);
            //TODO: verificar se o valor da constante ja foi incluida na tabela de simbolos
            gen_string = sym_string_declare(string_value);
            ok1 = match(STRING);
            if ( gen_string != NULL ) {
                strcpy(lexeme_of_id, gen_string->name);
                gen_write(lexeme_of_id, STRING);
                ok2 = match(SEMICOLON);
                return ok1 && ok2;
            }
        } else if ( lookahead->tag == ID) {
            strcpy(lexeme_of_id, lookahead->lexema);
            ok1 = match(ID);
            search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
            if (search_symbol != NULL) {
                type = search_symbol->type;
                gen_write(lexeme_of_id, type);
                ok2 = match(SEMICOLON);
                return ok1 && ok2;
            } else {
                printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
                return false;
            }
        }
    } else if (lookahead->tag == IF) {
        char label_else[MAX_CHAR];
        char label_end[MAX_CHAR];
        gen_label_name(label_else);
        gen_label_name(label_end);

        match(IF); // Com certeza ira existir um if
        if (!match(OPEN_PAR)) {
            printf("[ERRO] Faltando '(' na estrutura do comando if\n");
            return false;
        }
        
        // E(); //Expressao booleana -> Substituido por "B"
        if (!B()) {
            return false;
        }

        gen_cond_jump(label_else);
        if (!match(CLOSE_PAR)) {
            printf("[ERRO] Faltando ')' na estrutura do comando if\n");
            return false;
        }
        
        // Processa os comandos dentro do if
        if (!match(BEGIN)) {    
            printf("[ERRO] Faltando 'begin' na estrutura do comando if\n");
            return false;
        }

        
        statements(); // Processa comandos
        
        if (!match(END)) {    
            printf("[ERRO] Faltando 'end' na estrutura do comando if\n");
            return false;
        }

        gen_incond_jump(label_end);
        gen_label(label_else);

        // Verifica se ocorre um ELSE
        if (lookahead->tag == ELSE) {
            match(ELSE); // Com certeza vai ter um 'else'

            // Processa os comandos dentro do else
            if (!match(BEGIN)) {    
                printf("[ERRO] Faltando 'begin' na estrutura do comando else\n");
                return false;
            }

            statements(); // Processa comandos

            if (!match(END)) {    
                printf("[ERRO] Faltando 'end' na estrutura do comando else\n");
                return false;
            }
        }

        gen_label(label_end);
        return true;

    // Atribuicao ou Chamada de funcao
    } else if (lookahead->tag == ID) {
        // Guarda o nome do "ID" escrito
        char id_name[MAX_CHAR];
        strcpy(id_name, lookahead->lexema);
        match(ID); // Consome o ID

        // Verifica se o ID eh uma chamada de funcao
        if (lookahead->tag == '(') { 
            return func_call_cmd(id_name);
        
        
        // Verifica se o ID eh uma atribuicao
        } else if (lookahead->tag == ASSIGN) { 
            match(ASSIGN); // Consome o simbolo de igual
            
            // Verifica se a variavel ja foi declarada
            type_symbol_table_entry *var_entry = sym_find(id_name, &global_symbol_table_variables);
        
            if (!var_entry) {
                printf("[ERRO] Variavel nao declarada: %s\n", id_name);
                return false;
            }

            // Realiza a expressao dentro da atribuicao.
            int expr_type = E();
            
            // Resolve o que tiver de expressao apos o igual para atribuir o valor na variavel
            // Verifica se deu erro na atribuicao
            if (expr_type == ERROR) {
                printf("[ERRO] Expressao invalida apos atribuicao '='.\n");
                return false;
            }
            
            // Verifica se o tipo eh compativel com o tipo da variavel
            if (var_entry->type != expr_type) {
                printf("[ERRO] Tipo incompativel na atribuicao de '%s'\n", id_name);
                return false;
            }
            
            // Gera codigo de maquina para atribuicao
            gen_assign(id_name, var_entry->type);
            
            // Verifica se foi colocado ";" apos a atribuicao
            if (!match(SEMICOLON)) {
                printf("[ERRO] Esperado ';' apos atribuicao\n");
                return false;
            }

            // Retorna sucesso
            return true;
        
        // Se nao for nem chamada de funcao e nem atribuicao, gera erro
        } else {
            printf("[ERRO] Comando invalido '%s'\n", id_name);
            return false;
        }

    // While
    } else if (lookahead->tag == WHILE) {
        // Cria labels para controle do loop
        char label_start[MAX_CHAR];
        char label_end[MAX_CHAR];
        gen_label_name(label_start);
        gen_label_name(label_end);
    
        match(WHILE); // Consome o token WHILE
    
        // Verifica abertura de parênteses
        if (!match(OPEN_PAR)) {
            printf("[ERRO] Esperado '(' após 'while'\n");
            return false;
        }
    
        // Gera o label de início do loop (para retorno)
        gen_label(label_start);
    
        // Processa a condição booleana
        if (!B()) {
            printf("[ERRO] Condição inválida no 'while'\n");
            return false;
        }
    
        // Gera jump condicional para o final do loop se a condição for falsa
        gen_cond_jump(label_end);
    
        // Verifica fechamento de parênteses
        if (!match(CLOSE_PAR)) {
            printf("[ERRO] Esperado ')' após condição do 'while'\n");
            return false;
        }
    
        // Verifica abertura do bloco 'begin'
        if (!match(BEGIN)) {
            printf("[ERRO] Esperado 'begin' após 'while'\n");
            return false;
        }
    
        // Processa os comandos dentro do loop
        statements();
    
        // Verifica fechamento do bloco 'end'
        if (!match(END)) {
            printf("[ERRO] Esperado 'end' no final do 'while'\n");
            return false;
        }
    
        // Gera jump incondicional de volta ao início do loop
        gen_incond_jump(label_start);
    
        // Gera o label de final do loop
        gen_label(label_end);
    
        return true;
    
    // // Se no meio do codigo foi criado uma variavel, cria ela.
    // } else if (lookahead->tag == INT ||
    //         lookahead->tag == FLOAT ||
    //         lookahead->tag == CHAR ||
    //         lookahead->tag == STRING) {

    //     return declaration();
    
    } else if (lookahead->tag == END) {
        return false;

    } else if (lookahead->tag == ENDTOKEN) {
        return false;

    } else {
        printf("[ERRO] Comando desconhecido.\nTag=%d; Lexema=%s\n",lookahead->tag, lookahead->lexema);
        return false;
    }
}

/**
 * @brief Processa a implementacao de funcoes, verificando se estah igual com os prototipos declarados
 * Equivalente a regra de derivacao "Func_code" da gramatica
 * 
 * @details Esta funcao eh responsavel por:
 * 1. Validar se a funcao foi previamente declarada
 * 2. Verificar compatibilidade do tipo de retorno e o nome da funcao
 * 3. Validar os parametros (quantidade, tipos e nomes)
 * 4. Verificar a existencia de BEGIN/END do corpo da funcao
 * 
 * @return "true" Se estiver tudo certo
 * @return "false" Se tiver algum erro se a funcao nao for encontrada (escreveu ou deixou de escrever alguma parte) ou na implementacao
 * 
 * @note A funcao utiliza a tabela de simbolos de funcoes (TSF) para validacoes
 */
int function_statements() {
    type_symbol_function_entry *search_func; // Funcao procurada
    int ok = true; // Eh retornada no final com o resultado (true ou false, se nao achou funcao nehuma)
    char name[MAX_CHAR]; // Nome da funcao
    int return_type; // Tipo de retorno da funcao

    // So processa se for um tipo valido (INT, FLOAT, CHAR, STRING)
    // Processa enquanto houver funcoes (para permitir chamada de funcao aninhada)
    while (lookahead->tag == INT || lookahead->tag == FLOAT || 
        lookahead->tag == CHAR || lookahead->tag == STRING) {

        return_type = lookahead->tag; // Recebe o tipo de retorno escrito no codigo
        match(return_type); // Consome o tipo de retorno
        
        // Obtem o nome da funcao
        strcpy(name, lookahead->lexema);
        if (!match(ID)) {
            printf("[ERRO] Nome de funcao esperado apos o tipo\n");
            return false;
        }

        // Verifica se a funcao foi declarada
        search_func = sym_func_find(name);
        if (search_func == NULL) {
            printf("[ERRO] Funcao '%s' nao foi declarada\n", name);
            return false;
        }

        // Verifica tipo de retorno
        if (search_func->type != return_type) {
            printf("[ERRO] Tipo de retorno incompativel para '%s'. Esperado '%d', obtido '%d' na implementacao\n", name, search_func->type, return_type);
            return false;
        }

        // Consome os parenteses '('
        if (!match('(')) {
            printf("[ERRO] '(' esperado apos o nome da funcao na implementacao\n");
            return false;
        }

        // Processa os parametros
        int param_cont = 0; // Recebe a qtd de parametros escritos no codigo
        while (lookahead->tag == INT || lookahead->tag == FLOAT || 
               lookahead->tag == CHAR || lookahead->tag == STRING) {
            
            // Verifica se excedeu o numero de parametros declarados
            if (param_cont >= search_func->nparams) {
                printf("[ERRO] Quantidade de parametros na implementacao eh maior do que a quantidade de parametros na declaracao\n");
                return false;
            }

            // Valida o tipo do parametro
            int param_type = lookahead->tag;
            if (param_type != search_func->params[param_cont].type) {
                printf("[ERRO] Tipo do parametro '%d' incompativel na implementacao. Esperado '%d', obtido '%d'\n", param_cont+1, search_func->params[param_cont].type, param_type);
                return false;
            }
            match(param_type); // Cosnome o tipo

            // Valida o nome do parametro
            char param_name[MAX_CHAR];
            strcpy(param_name, lookahead->lexema);
            if (strcmp(param_name, search_func->params[param_cont].name) != 0) {
                printf("[ERRO] Nome do parametro '%d' incompativel na implementacao. Esperado '%s', obtido '%s'\n", param_cont+1, search_func->params[param_cont].name, param_name);
                return false;
            }
            match(ID); // Cosome o nome do parametro

            param_cont++; // Qtd de parametros += 1

            // Verifica se tem virgula (mais um parametro) ou se acabou (agora vem o fecha parenteses ')')
            if (lookahead->tag == ',') {
                match(',');

                // Se o proximo token nao for uma nova variavel, retorna erro
                if (lookahead->tag != INT && lookahead->tag != FLOAT && 
                    lookahead->tag != CHAR && lookahead->tag != STRING) {
                    printf("[ERRO] Esperado um novo parametro apos a virgula ','\n");
                    return false;
                }
            
            // Se nao tiver virgula e nao tiver fechado os parametros, retorna erro
            } else if (lookahead->tag != ')') {
                printf("[ERRO] Esperado virgula apos parametro.\n");
                return false;
            }
        } 

        // Verifica se a quantidade de parametros capturados eh igual a qtd da funcao
        if (param_cont < search_func->nparams) {
            printf("[ERRO] Quantidade de parametros eh menor do que quantidade de parametros na declaracao\n");
            return false;
        }

        // Consome o fecha parenteses ')'
        if (!match(')')) {
            printf("[ERRO] ')' esperado apos parametros\n");
            return false;
        }

        // Declaracao das variaveis da funcao:
        // Declara as variaveis dos parametros como globais
        type_symbol_table_entry *search_var;
        for (int i = 0; i < search_func->nparams; i++) {
            // Verifica se a variavel ja esta declarada
            search_var = sym_find(search_func->params[i].name, &global_symbol_table_variables);
            if (search_var != NULL) {
                printf("[ERRO] Variavel '%s' da funcao '%s' ja foi declarada globalmente.\n", name, search_func->name);
                return false;
            }

            // Declara a variavel
            sym_declare(search_func->params[i].name, search_func->params[i].type, 0, &global_symbol_table_variables);
        }

        // Apos processar os parametros e antes do 'begin'
        gen_label(search_func->label); // Emite o label da funcao no Assembly

        // Verifica o comando BEGIN
        if (!match(BEGIN)) {
            printf("[ERRO] Comando 'begin' esperado apos declaracao da funcao\n");
            return false;
        }

        // Processa o corpo da funcao
        statements();

        // Verifica o comando END
        if (!match(END)) {
            printf("[ERRO] 'end' esperado no final da funcao\n");
            return false;
        }
        
        // Gera codigo de maquina para instrucao de retorno para o ponto de chamada da funcao
        gen_ret();

        ok = true; // Sucesso
    
    
    } 
    
    // Se o lookahead nao for um tipo e nem fim de arquivo, retorna erro
    if (lookahead->tag != ENDTOKEN) {
        printf("[ERRO] Esperado implementacao de funcao ou fim de arquivo.\n");
        ok = false;
    }

    // Retorna a saida final (sucesso ou falha)
    return ok;
}


/**
 * @brief Regra de derivacao para chamada de funcao
 * 
 * @param func_name Nome da funcao chamada
 * @return "true" Se sucesso 
 * @return "false" Se falha
 */
int func_call_cmd(char *func_name) {
    // Verifica se a funcao exite
    type_symbol_function_entry *func_entry;
    func_entry = sym_func_find(func_name);
    if (func_entry == NULL) {
        printf("[ERRO] Funcao '%s' nao foi declarada.\n", func_name);
        return false;
    }
    
    // Consome '('
    if (!match(OPEN_PAR)) {
        printf("[ERRO] '(' esperado apos '%s'.\n", func_name);
        return false;
    }

    int param_count = 0;

    // Faz um loop sobre os argumentos da chamada da funcao ateh encontrar ')'
    while (lookahead->tag != ')') {
        // Processa cada parametro (expressao ou variavel)
        // Verifica se nao passou da quantidade de parametros da funcao original
        if (param_count >= func_entry->nparams) {
            printf("[ERRO] Muitos argumentos em '%s'. Esperado '%d'.\n", func_name, func_entry->nparams);
            return false;
        }


        // Chama E(), que devolve o tipo da variavel/valor ou ERROR
        int actual_type = E();
        if (actual_type == ERROR) {
            printf("[ERRO] Expressao invalida no arg '%d' de '%s'.\n", param_count+1, func_name);
            return false;
        }
        
        // Compara tipo passado com o tipo do prototipo da funcao
        int expected_type = func_entry->params[param_count].type; // Pega o tipo no prototipo
        if (actual_type != expected_type) { 
            printf("[ERRO] Tipo do arg '%d' da funcao '%s' estah incorreto. Esperado '%d', obtido '%d'.\n", 
                param_count+1, func_name, expected_type, actual_type);
            return false;
        }

        gen_assign(func_entry->params[param_count].name, actual_type);
        param_count++; // Aumenta o contador de parametros (pula para o proximo parametro na proxima iteracao)


        // Consome virgula
        if (lookahead->tag == COMMA) {
            match(COMMA);
            
            // Se o proximo token nao for uma entrada esperada para chamada de funcao, retorna erro
            if (lookahead->tag != NUM && lookahead->tag != MINUS && 
                lookahead->tag != STRING && lookahead->tag != CHARACTER_LITERAL && lookahead->tag != ID) {
                printf("[ERRO] Esperado um novo parametro apos a virgula ','\n");
                return false;
            }
        // Se apos a virgula nao tiver um fecha parenteses, da erro
        } else if (lookahead->tag != CLOSE_PAR) {
            printf("[ERRO] Esperado ',' ou ')' apos argumento '%d' de '%s'.\n",
                param_count, func_name);
            return false;
        }
    }

    // Consome ')'
    if (!match(CLOSE_PAR)) {
        printf("[ERRO] ')' esperado apos argumentos de '%s'.\n", func_name);
        return false;
    }

    // Verifica se a quantidade de parametros passados eh diferente da quantidade de parametros do prototipo da funcao
    if (param_count != func_entry->nparams) {
        // Se for diferente, gera erro
        printf("[ERRO] Numero de parametros incorreto em '%s'. Esperado '%d', obtido '%d'\n", 
               func_name, func_entry->nparams, param_count);
        return false;
    }

    // Consome ';'
    if (!match(SEMICOLON)) {
        printf("[ERRO] Esperado ';' apos chamada da funcao '%s'\n", func_name);
        return false;
    }

    // Gera codigo de montagem para salto para o codigo da funcao
    gen_call(func_entry->label);

    return true;
}

/**
 * @brief Regra de derivação que analiza expressoes booleanas
 *        no padrao '[id | expr] op_rel [id | expr]'
 * 
 */
int B() {
    // Processa o primeiro termo (mais alta precedência: &&)
    if (!BTerm()) {
        return false;
    }

    // Processa operadores || (menor precedência)
    while (lookahead->tag == LOGICAL_OR) {
        match(LOGICAL_OR);
        
        if (!BTerm()) {
            printf("[ERRO] Expressão inválida após ||\n");
            return false;
        }
        
        gen_logical_or(); // Gera código para ||
    }

    return true;
}

// Processa um termo
int BTerm() {
    // Processa a expressão relacional ou primária
    if (!BFactor()) {
        return false;
    }

    // Processa operadores && (maior precedência)
    while (lookahead->tag == LOGICAL_AND) {
        match(LOGICAL_AND);
        
        if (!BFactor()) {
            printf("[ERRO] Expressão inválida após &&\n");
            return false;
        }
        
        gen_logical_and(); // Gera código para &&
    }

    return true;
}

// Processa um fator
int BFactor() {
    // Processa uma expressão relacional (a > b) ou primária (valor booleano)
    if (E() == ERROR) {
        printf("[ERRO] Expressão inválida\n");
        return false;
    }

    // Verifica operadores relacionais
    if (lookahead->tag == EQUAL || lookahead->tag == NE || 
        lookahead->tag == LT || lookahead->tag == GT || 
        lookahead->tag == LE || lookahead->tag == GE) {
        
        int operator;
        if (!boolOperator(&operator)) {
            return false;
        }

        if (E() == ERROR) {
            printf("[ERRO] Expressão direita inválida\n");
            return false;
        }

        gen_bool(operator);
    }

    return true;
}


int boolOperator(int *operator) {
    int lookahead_tag;
    lookahead_tag = lookahead->tag;
    *operator = -1;
    
    if (lookahead_tag == EQUAL ||
        lookahead_tag == NE ||
        lookahead_tag == LT ||
        lookahead_tag == GT ||
        lookahead_tag == LE ||
        lookahead_tag == GE) {
            *operator = lookahead_tag;
            if (!match(lookahead_tag)) {
                return false;
            }
            return true;
    } else {
        printf("[ERRO] Operador relacional inesperado: %s\n", lookahead->lexema);
        return false;
    }
}

//------
/* Funcoes que representam a gramatica que reconhece expressoes aritmeticas */
/* Elaborada nas primeiras aulas */
/* Funcoes modificadas para retornarem o tipo da variavel ou valor passado */

// E -> T ER
int E() {
    int type_t = T();
    if (type_t == ERROR) {
        return ERROR;
    }
    
    return ER(type_t);
}

// ER -> (+ T ER) | (‑ T ER) | ε
int ER(int in_type) {
    // Soma
    if (lookahead->tag == PLUS)  { 
        match(PLUS);
        int type_t = T();
        if (type_t == ERROR){
            return ERROR;
        }

        // Verifica coerencia de soma
        if (!((in_type == INT && type_t == INT) || (in_type == FLOAT && type_t == FLOAT))) {
            printf("[ERRO] Tipos incompativeis em soma: '%d' e '%d'\n", in_type, type_t);
            return ERROR;
        }
        genAdd(); // Gera codigo de montagem para a soma

        return ER(in_type);

    // Subtracao
    } else if (lookahead->tag == MINUS) {
        match(MINUS);

        int type_t = T();
        
        if (type_t == ERROR) {
            return ERROR;
        }

        // Verifica coerencia de soma
        if (!((in_type == INT && type_t == INT) || (in_type == FLOAT && type_t == FLOAT))) {
            printf("[ERRO] Tipos incompativeis em subtracao: '%d' e '%d'\n", in_type, type_t);
            return ERROR;
        }

        genSub(); // Gera codigo de montagem para a subtracao

        return ER(in_type);    
    
    // Fim de E
    } else {
        // Nao tem mais operadores de adicao/subtracao
        return in_type;
    }
}

// T -> F TR
int T() {
    int type_f = F();
    if (type_f == ERROR) {
        return ERROR;
    }

    return TR(type_f);
}


// TR -> (* F TR) | (/ F TR) | ε
int TR(int in_type) {
    // Se for multiplicacao
    if (lookahead->tag == MULT) { 
        match(MULT);
        int type_f = F();
        if (type_f == ERROR) {
            return ERROR;
        }

        // Verifica coerencia de multiplicacao
        if (!((in_type == INT && type_f == INT) || (in_type == FLOAT && type_f == FLOAT))) {
            printf("[ERRO] Tipos incompativeis em multiplicacao: '%d' e '%d'\n", in_type, type_f);
            return ERROR;
        }

        genMult(); // Gera codigo de montagem para a multiplicacao

        return TR(in_type);

    // Se for divisao
    } else if (lookahead -> tag == DIV) {
        match(DIV);

        int type_f = F();
        if (type_f == ERROR) {
            return ERROR;
        }
        
        // Verifica coerencia de divisao
        if (!((in_type == INT && type_f == INT) || (in_type == FLOAT && type_f == FLOAT))) {
            printf("[ERRO] Tipos incompatíveis em divisão: %d e %d\n", in_type, type_f);
            return ERROR;
        }
        genDiv(); // Gera codigo de montagem para a divisao

        return TR(in_type);

    // Fim de T
    } else {
        // Nao tem mais operadores de multiplicacao/divisao
        return in_type;
    }
}

// F -> '(' E ')' | -NUM | NUM | ID | CHARACTER_LITERAL | STRING
// Alterado para identificar subtracao unaria
int F() {

    // Se for parenteses, calcula a expressao dentro dele
    if (lookahead->tag == OPEN_PAR) {
        match(OPEN_PAR);

        int type_e = E();
        if (type_e == ERROR) {
            return ERROR;
        }
        
        if (!match(CLOSE_PAR)) {
            printf("[ERRO] Esperado ')'\n");
            return ERROR;
        }
        return type_e;

    // Se for um operador unario '-'
    } else if (lookahead->tag == MINUS) {
        match(MINUS); // Consome o '-'
        
        // Processa o operando (pode ser outro unario, numero, etc.)
        int type_f = F();
        if (type_f == ERROR){
            return ERROR;
        } 

        // Verifica se o tipo eh válido para negacao
        if (type_f != INT && type_f != FLOAT) {
            printf("[ERRO] Operando inválido para '-'\n");
            return ERROR;
        }

        genNeg(type_f); // Gera codigo de montagem para valores negativos unarios

        return type_f;

    // Se for um literal de string
    } else if (lookahead->tag == STRING) {
        // Extrai o conteudo da string (removendo as aspas)
        char string[MAX_CHAR];
        strcpy(string, lookahead->lexema); // Pega o nome
        
        // Declara a string na tabela de simbolos
        type_symbol_table_string_entry *str_entry = sym_string_declare(string);
        
        // Gera codigo para carregar o endereco da string
        genString(str_entry->name);
        
        match(STRING);
        return STRING;
    

    // Se for um numero
    } else if (lookahead->tag == NUM) { // Reconhece numeros
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        match(NUM);

        // Verifica se eh float (contem ponto)
        if (strchr(lexema, '.') != NULL) {
            // Verifica se atingiu o limite maximo de floats ja criados
            if (float_const_count >= MAX_FLOAT) {
                printf("[ERRO] Limite de constantes float excedido.\n");
                return ERROR;
            }

            // Cria uma label unica usando o contador
            char label[32];
            sprintf(label, "__float_const_%d", float_const_count);
            // Armazena na struct
            strcpy(float_constants[float_const_count].label, label); // Guarda a label
            strcpy(float_constants[float_const_count].value, lexema); // Guarda o valor do float
            float_const_count++; // Contador = Contador + 1

            // Gera codigo para carregar o float
            genFloat(label); // Float

            return FLOAT; // Retorna o tipo
        } else { // Se for um valor inteiro, nada muda
            genNum(lexema); // Inteiro

            return INT; // Retorna o tipo
        }

    // Se for um ID (variavel)
    } else if (lookahead->tag == ID) { // Reconhece IDs
        char var_name[MAX_TOKEN];
        strcpy(var_name, lookahead->lexema);
        match(ID);

        // Procura pelo tipo da variavel
        type_symbol_table_entry *var = sym_find(var_name, &global_symbol_table_variables);
        if (!var) {
            printf("[ERRO] Variavel nao declarada: '%s'\n", var_name);
            return ERROR;
        }

        gen_id(var_name); // Funcao para empilhar variaveis na memoria
        return var->type;
    
    // Se for um literal de caractere (char)
    } else if (lookahead->tag == CHARACTER_LITERAL) {
        // Extrai o valor do caractere (exemplo: 'a' -> a)
        char value = lookahead->lexema[1]; // Pega o caractere (ex: 'a' em 'a')
        genChar(value); // Gera código para empilhar o valor do caractere
        match(CHARACTER_LITERAL);
        return CHAR;
    

    // Se nao for nem um ID e nem um Numero, retorna erro
    } else {
        return ERROR;
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

    program(); //Chamada da derivacao/funcao inicial da gramatica

    fclose(output_file);
    return 1;
}