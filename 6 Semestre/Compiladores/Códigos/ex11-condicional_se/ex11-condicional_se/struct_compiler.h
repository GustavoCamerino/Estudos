/**
 * @file struct_compiler.h
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo para definicao de constantes e estruturas de dados do Sistema
 *        Compilador de C Simplificado
 * @version 0.4
 * @date 2021-12-09
 */

#ifndef _STRUCT_COMPILER_
#define _STRUCT_COMPILER_

#define MAX_CHAR 32
#define MAX_TOKEN 32

#define true 1
#define false 0

#define ENDTOKEN '\0'
#define ERROR -1
#define NUM 1
#define PLUS '+'
#define MINUS '-'
#define MULT '*'
#define DIV '/'
#define OPEN_PAR '('
#define CLOSE_PAR ')'
#define SEMICOLON ';'
#define DOUBLE_QUOTES '"'

#define ID 256
#define IF 257
#define ELSE 258
#define WHILE 260
#define DO 261
#define READ 262
#define WRITE 263
#define INT 264
#define STRING 265
#define FLOAT 266
#define CHAR 267
#define BEGIN 268
#define END 269

#define ASSIGN '='
#define EQUAL 270
#define NE 271
#define GE 272
#define LE 273
#define GT '>'
#define LT '<'
#define AND 274
#define OR 275

struct st_token {
    int tag;
    char lexema[MAX_CHAR];
    int value;
};
typedef struct st_token type_token;

#endif //_STRUCT_COMPILER_