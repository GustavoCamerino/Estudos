/**
 * @file ex1-soma_e_sub-AnaliseSintatica.c
 * @author Gustavo Camerino de Carvalho
 * @brief  Analisador sintático descendente - Compiladores - Prof. Ivairton
 * @version 0.1
 * @date 2024-12-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Constantes
#define MAX_CHAR 32
#define true 1
#define false 0
// Variaveis globais
int pos = 0;
char string[MAX_CHAR];
char lookahead;
char strror[MAX_CHAR];

// Prototipos
int list();
int listR();
int digit();
int match(char c);
void nextToken();

// Funcao principal
int main()
{

    int acept = false;

    printf("Informe uma cadeia:");
    scanf("%s", string); // leitura da cadeia

    lookahead = string[0]; // inicializacao do lookahead

    acept = list(); // Chamada da derivacao/funcao inicial da gramatica

    if (acept)
    {
        printf("Cadeia PERTENCENTE a linguagem\n");
    }
    else
    {
        printf("Cadeia NAO pertencente a linguagem\n");
    }

    return 1;
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

// Funcao da regra de derivacao 'list'
int list()
{
    if (digit() && listR())
        return true;
    return false;
}

// Funcao da regra de derivacao 'listR'
int listR()
{
    int test1, test2, test3;
    if (lookahead == '+')
    {
        test1 = match('+');
        test2 = digit();
        test3 = listR();
        return test1 && test2 && test3;
    }
    else if (lookahead == '-')
    {
        test1 = match('-');
        test2 = digit();
        test3 = listR();
        return test1 && test2 && test3;
    }
    else
    {
        if (match('\0'))
            return true;
        printf("Erro,era esperado =/- ou fim mas ocorreu %c na posição %d\n", lookahead, pos);
        return false;
    }
}

// Funcao da regra de derivacao 'digit''
int digit()
{
    if (
        match('0') || match('1') ||
        match('2') || match('3') ||
        match('4') || match('5') ||
        match('6') || match('7') ||
        match('8') || match('9'))
    {
        return true;
    }
    printf("Erro, era esperado um digito na pos %d\n", pos);
    return false;
}