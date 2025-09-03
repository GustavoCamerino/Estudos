/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.5
 * @date 2022-02-04
 */

#include "synt.h"

type_token *lookahead;
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
extern char output_file_name[MAX_CHAR];
extern FILE *output_file;

int match(int token_tag) {
    if (lookahead->tag == token_tag) {
        lookahead = getToken();
        return true;
    }
    printf("[ERRO] Entrada esperada: %s\n", lookahead->lexema);
    return false;
}

void program(void) {
    gen_preambule();
    declarations();
    gen_preambule_code();
    statements();
    gen_epilog_code();
    gen_data_section();
}

void declarations(void) {
    while (declaration());
}

int declaration(void) {
    type_symbol_table_entry *search_symbol;
    int ok1, ok2;
    char var_name[MAX_CHAR];
    int var_type;

    var_type = lookahead->tag;
    if (var_type == INT || var_type == FLOAT || var_type == CHAR || var_type == STRING) { 
        match(var_type);
        strcpy(var_name, lookahead->lexema);
        search_symbol = sym_find(var_name, &global_symbol_table_variables);

        if (search_symbol != NULL) {
            printf("[ERRO] Variavel '%s' ja declarada.\n", var_name); 
            return false;
        } else {
            sym_declare(var_name, var_type, 0, &global_symbol_table_variables);
            ok1 = match(ID);
            ok2 = match(SEMICOLON);
            return ok1 && ok2;
        }
    } else {
        return false;
    }
}

void statements(void) {
    while (statement());
}

int statement(void) {
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
        if (lookahead->tag == STRING) {
            strcpy(string_value, lookahead->lexema);
            gen_string = sym_string_declare(string_value);
            match(STRING);
            if (gen_string != NULL) {
                strcpy(lexeme_of_id, gen_string->name);
                gen_write(lexeme_of_id, STRING);
                match(SEMICOLON);
            }
        } else if (lookahead->tag == ID) {
            strcpy(lexeme_of_id, lookahead->lexema);
            match(ID);
            search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
            if (search_symbol != NULL) {
                type = search_symbol->type;
                gen_write(lexeme_of_id, type);
                match(SEMICOLON);
                return true;
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

        match(IF);
        match(OPEN_PAR);
        if (!B()) return false;
        gen_cond_jump(label_else);
        match(CLOSE_PAR);
        
        match(BEGIN);
        statements();
        match(END);

        gen_incond_jump(label_end);
        gen_label(label_else);

        if (lookahead->tag == ELSE) {
            match(ELSE);
            match(BEGIN);
            statements();
            match(END);
        }
        gen_label(label_end);
        return true;
    } else if (lookahead->tag == END || lookahead->tag == ENDTOKEN) {
        return false;
    } else {
        printf("[ERRO] Comando desconhecido.\nTag=%d; Lexema=%s\n", lookahead->tag, lookahead->lexema);
        return false;
    }
}

int B() {
    return B_and_or();
}

int B_and_or() {
    int b1 = B_single();
    if (!b1) return false;

    while (lookahead->tag == AND || lookahead->tag == OR) {
        int operator = lookahead->tag;
        match(operator);
        int b2 = B_single();
        if (!b2) return false;

        if (operator == AND) {
            fprintf(output_file, "; Operador AND\n");
            fprintf(output_file, "\tpop rbx\n");
            fprintf(output_file, "\tpop rax\n");
            fprintf(output_file, "\tand rax, rbx\n");
            fprintf(output_file, "\tpush rax\n");
        } else if (operator == OR) {
            fprintf(output_file, "; Operador OR\n");
            fprintf(output_file, "\tpop rbx\n");
            fprintf(output_file, "\tpop rax\n");
            fprintf(output_file, "\tor rax, rbx\n");
            fprintf(output_file, "\tpush rax\n");
        }
    }
    return true;
}

int B_single() {
    int operator;
    char lexeme[MAX_CHAR];

    if (lookahead->tag == ID) {
        strcpy(lexeme, lookahead->lexema);
        match(ID);
        gen_push_var(lexeme);
    } else if (!E()) {
        printf("[ERRO] Operando esquerdo inválido na expressão booleana.\n");
        return false;
    }

    if (!boolOperator(&operator)) {
        printf("[ERRO] Operador relacional esperado.\n");
        return false;
    }

    if (lookahead->tag == ID) {
        strcpy(lexeme, lookahead->lexema);
        match(ID);
        gen_push_var(lexeme);
    } else if (!E()) {
        printf("[ERRO] Operando direito inválido na expressão booleana.\n");
        return false;
    }

    gen_bool(operator);
    return true;
}

int boolOperator(int *operator) {
    int lookahead_tag = lookahead->tag;
    *operator = -1;
    
    if (lookahead_tag == EQUAL || lookahead_tag == NE || lookahead_tag == LT ||
        lookahead_tag == GT || lookahead_tag == LE || lookahead_tag == GE) {
        *operator = lookahead_tag;
        match(lookahead_tag);
        return true;
    }
    return false;
}

int E() {
    int b1, b2;
    b1 = T();
    if (b1) 
        b2 = ER();
    return b1 && b2;
}

int ER() {
    if (lookahead->tag == '+')  { 
        int b1, b2;
        match('+');
        b1 = T();
        genAdd();
        if (b1) 
            b2 = ER();
        return b1 && b2;
    } else if (lookahead->tag == '-') {
        int b1, b2;
        match('-');
        b1 = T();
        genSub();
        if (b1)
            b2 = ER();
        return b1 && b2;      
    } else if (lookahead->tag == ')' || lookahead->tag == ENDTOKEN || 
               lookahead->tag == '*' || lookahead->tag == '/') {
        return true;
    } else {
        return false;
    }
}

int T() {
    int b1, b2;
    b1 = F();
    if (b1)
        b2 = TR();
    return b1 && b2;
}

int TR() {
    if (lookahead->tag == '*') { 
        int b1, b2;
        match('*');
        b1 = F();
        genMult();
        if (b1)
            b2 = TR();
        return b1 && b2;
    } else if (lookahead->tag == '/') {
        int b1, b2;
        match('/');
        b1 = F();
        genDiv();
        if (b1)
            b2 = TR();
        return b1 && b2;
    } else if (lookahead->tag == ')' || lookahead->tag == ENDTOKEN || 
               lookahead->tag == '+' || lookahead->tag == '-') {
        return true;
    } else {
        return false;
    }
}

int F() {
    if (lookahead->tag == '(') {
        int b1, b2;
        match('(');
        b1 = E();
        if (b1)
            b2 = match(')');
        return b1 && b2;
    } else if (lookahead->tag == NUM) {
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        int b1 = match(NUM);
        genNum(lexema);
        return b1;
    } else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    initSymbolTableVariables(&global_symbol_table_variables);
    initSymbolTableString();

    if (argc != 2) {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }
    
    initLex(argv[1]);
    lookahead = getToken();

    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, ".asm");
    output_file = fopen(output_file_name, "w+");

    program();

    fclose(output_file);
    return 1;
}