/**
 * @file lex.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador lexico
 * @version 0.5
 * @date 2022-03-16
 */

#include "lex.h"

int pos;
FILE *input_file;

type_token key_words[] = {
    {IF, "if", 0},
    {ELSE, "else", 0},
    {WHILE, "while", 0},
    {DO, "do", 0},
    {NUM, "integer", 0},
    {READ, "read", 0},
    {WRITE, "write", 0},
    {INT, "int", 0},
    {FLOAT, "float", 0},
    {STRING, "string", 0},
    {CHAR, "char", 0},
    {BEGIN, "begin", 0},
    {END, "end", 0},
    {EQUAL, "==", 0},
    {NE, "!=", 0},
    {GE, ">=", 0},
    {LE, "<=", 0},
    {AND, "&&", 0},
    {OR, "||", 0}
};

void initLex(char input_file_name[]) {
    input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        printf("[ERRO]\n\tArquivo de entrada não encontrado: %s\n\n", input_file_name);
        exit(EXIT_FAILURE);
    }
}

type_token *getToken() {
    char buffer[MAX_CHAR];
    int pos_buffer;
    type_token *token;
    type_token *key_found;
    char ch;
    
    pos_buffer = 0;
    token = (type_token*) malloc(sizeof(type_token));
    strcpy(buffer, "");
    ch = fgetc(input_file);

    while (ch == ' ' || ch == '\t' || ch == '\n') {
        ch = fgetc(input_file);
    }

    if (isdigit(ch)) {
        while (isdigit(ch)) {
            buffer[pos_buffer++] = ch;
            ch = fgetc(input_file);
        }
        if (ch == '.') {
            buffer[pos_buffer++] = ch;
            ch = fgetc(input_file);
            while (isdigit(ch)) {
                buffer[pos_buffer++] = ch;
                ch = fgetc(input_file);
            }
        }
        ungetc(ch, input_file);
        buffer[pos_buffer] = '\0';
        token->tag = NUM;
        strcpy(token->lexema, buffer);
    } else if (isalpha(ch)) {
        buffer[pos_buffer++] = ch;
        ch = fgetc(input_file);
        while (isalnum(ch)) {
            buffer[pos_buffer++] = ch;
            ch = fgetc(input_file);
        }
        ungetc(ch, input_file);
        buffer[pos_buffer] = '\0';
        key_found = keyWordFind(buffer);
        if (key_found != NULL) {
            token->tag = key_found->tag;
            strcpy(token->lexema, key_found->lexema);
            token->value = key_found->value;
        } else {
            token->tag = ID;
            strcpy(token->lexema, buffer);
            token->value = 0;
        }
    } else if (ch == PLUS) {
        token->tag = PLUS;
        strcpy(token->lexema, "+");
        token->value = 0;
    } else if (ch == MINUS) {
        token->tag = MINUS;
        strcpy(token->lexema, "-");
        token->value = 0;
    } else if (ch == MULT) {
        token->tag = MULT;
        strcpy(token->lexema, "*");
        token->value = 0;
    } else if (ch == DIV) {
        token->tag = DIV;
        strcpy(token->lexema, "/");
        token->value = 0;
    } else if (ch == OPEN_PAR) {
        token->tag = OPEN_PAR;
        strcpy(token->lexema, "(");
        token->value = 0;
    } else if (ch == CLOSE_PAR) {
        token->tag = CLOSE_PAR;
        strcpy(token->lexema, ")");
        token->value = 0;
    } else if (ch == SEMICOLON) {
        token->tag = SEMICOLON;
        strcpy(token->lexema, ";");
        token->value = 0;
    } else if (ch == ASSIGN) {
        ch = fgetc(input_file);
        if (ch == ASSIGN) {
            token->tag = EQUAL;
            strcpy(token->lexema, "==");
            token->value = 0; 
        } else {
            ungetc(ch, input_file);
            token->tag = ASSIGN;
            strcpy(token->lexema, "=");
            token->value = 0;
        }
    } else if (ch == LT) {
        ch = fgetc(input_file);
        if (ch == ASSIGN) {
            token->tag = LE;
            strcpy(token->lexema, "<=");
            token->value = 0;
        } else {
            ungetc(ch, input_file);
            token->tag = LT;
            strcpy(token->lexema, "<");
            token->value = 0;
        }
    } else if (ch == GT) {
        ch = fgetc(input_file);
        if (ch == ASSIGN) {
            token->tag = GE;
            strcpy(token->lexema, ">=");
            token->value = 0;
        } else {
            ungetc(ch, input_file);
            token->tag = GT;
            strcpy(token->lexema, ">");
            token->value = 0;
        }
    } else if (ch == '!') {
        ch = fgetc(input_file);
        if (ch == ASSIGN) {
            token->tag = NE;
            strcpy(token->lexema, "!=");
            token->value = 0;
        } else {
            ungetc(ch, input_file);
            token->tag = ERROR;
            strcpy(token->lexema, "!");
        }
    } else if (ch == '&') {
        ch = fgetc(input_file);
        if (ch == '&') {
            token->tag = AND;
            strcpy(token->lexema, "&&");
            token->value = 0;
        } else {
            ungetc(ch, input_file);
            token->tag = ERROR;
            strcpy(token->lexema, "&");
        }
    } else if (ch == '|') {
        ch = fgetc(input_file);
        if (ch == '|') {
            token->tag = OR;
            strcpy(token->lexema, "||");
            token->value = 0;
        } else {
            ungetc(ch, input_file);
            token->tag = ERROR;
            strcpy(token->lexema, "|");
        }
    } else if (ch == DOUBLE_QUOTES) {
        buffer[pos_buffer++] = ch;
        ch = fgetc(input_file);
        while (ch != DOUBLE_QUOTES && pos_buffer - 1 < MAX_CHAR) {
            buffer[pos_buffer++] = ch;
            ch = fgetc(input_file);
        }
        buffer[pos_buffer++] = DOUBLE_QUOTES;
        buffer[pos_buffer] = '\0';
        token->tag = STRING;
        strcpy(token->lexema, buffer);
        token->value = 0;
    } else if (ch == EOF) {
        token->tag = ENDTOKEN;
        strcpy(token->lexema, "\0");
    } else {
        token->tag = ERROR;
        strcpy(token->lexema, "");
    }

    return token;
}

type_token *keyWordFind(char *word) {
    int i = 0;
    while (key_words[i].lexema[0] != '\0') {
        if (strcmp(word, key_words[i].lexema) == 0)
            return &key_words[i];
        i++;
    }
    return NULL;
}