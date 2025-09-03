/**
 * UFMT -- Ciencia da Computacao
 * Compiladores - Prof. Ivairton
 *
 * Exemplo 4 - Analisador sintático a partir da TAS
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAX_CHAR 32
#define true 1
#define false 0
#define ERROR -1

// Regras e simbolos da gramatica
#define E 10
#define ER 11
#define T 12
#define TR 13
#define F 14
// Terminais:
#define id 0
#define sum 1
#define mult 2
#define o_par 3
#define c_par 4
#define end 5
#define empty 6

// Definicao de tipos
// String
typedef struct t_arr_int
{
    int ruler[MAX_CHAR];
} typeArrayInt;

// Stack
typedef struct t_stck
{
    int stack[MAX_CHAR];
    int count;
} typeStack;

// Variaveis globais
int pos = 0;
char string[MAX_CHAR];
char lookahead;
typeArrayInt TAS[5][6] = {
    {T, ER} {2}, {ERROR}, {ERROR}, {T, ER}, {ERROR}, {ERROR}, {ERROR}, {sum, T, ER}, {ERROR}, {ERROR}, {empty}, {empty}, {F, TR}, {ERROR}, {ERROR}, {F, TR}, {ERROR}, {ERROR}, {ERROR}, {empty}, {mult, F, TR}, {ERROR}, {empty}, {empty}, {id}, {ERROR}, {ERROR}, {o_par, E, c_par}, {ERROR}, {ERROR}};
typeStack stack;

// Prototipos
int push(int);
int pop();
void driver();
int digit();
int match(char c);
void nextToken();
void driver(char c);

void driver(char c)
{
    int a = lookahead;
    int x;
    int flag = 10;
    push(c);

    if (x < flag)
    {
        match(x);
    }
    else if ()
    {
    }
}
// Manipulacao da pilha
int push(int value)
{
    if (stack.count < MAX_CHAR)
    {
        stack.stack[stack.count++] = value;
        return true;
    }
    return ERROR;
}

int pop()
{
    if (stack.count > 0)
    {
        return stack.stack[--stack.count];
    }
    return ERROR;
}

// Verifica o proximo caracter (a frente) na cadeia eh o esperado
int match(char c)
{
    if (lookahead == c)
    {
        nextToken();
        return true;
    }
    return false;
}

// Funcao que passa ao proximo simbolo da cadeia
void nextToken()
{
    pos++;
    lookahead = string[pos];
}

// Funcao da regra de derivacao 'digit''
int digit()
{
    char ch;
    ch = lookahead;
    if (
        match('0') || match('1') ||
        match('2') || match('3') ||
        match('4') || match('5') ||
        match('6') || match('7') ||
        match('8') || match('9'))
    {
        // Adicao de comando para geracao de codigo:
        //...
        return true;
    }
    return false;
}

// Funcao principal
int main()
{

    // TAS inicializada em sua declaracao, conforme conteudo de aula.

    stack.count = 0; // Inicializacao do contador da pilha
    push(end);
    push(E);

    int acept = false;

    printf("Informe uma cadeia:");
    // scanf("%s", string); //leitura da cadeia
    strcpy(string, "2+3");

    lookahead = string[0]; // inicializacao do lookahead

    acept = E(); // Chamada da derivacao/funcao inicial da gramatica

    if (acept)
    {
        printf("Cadeia PERTENCENTE a linguagem!\n");
    }
    else
    {
        printf("Cadeia NAO pertencente a linguagem.\n");
    }

    return 1;
}