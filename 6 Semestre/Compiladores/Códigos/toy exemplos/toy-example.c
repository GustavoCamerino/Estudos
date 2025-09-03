/**
 * @file toy-example.c
 * @author Gustavo Camerino de Carvalho
 * @brief Exemplo 1 - Primerio experimento: analisador sintático descendente
 * @version 0.1
 * @date 2025-02-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>

//  Constantes

#define MAX_CHAR 32
#define true 1
#define false 0

// Variaveis glovais

int pos = 0;
char string[MAX_CHAR];
char lookahead;

// Prototipos
int list();
int listR();
int digit();
int match(char c);
void nextToken();

//  Verifica o proximo caracter (a frente) na cadeia eh o esperado
/**
 * @brief Verifico se minha posição atual corresponde a tal simbolo
 *        Se sim return true | Se não return false
 *
 * @param c
 * @return int
 */
int match(char c) //  <--- Verifica Compatibilidade / Igualdade
{
    if (lookahead == c)
    {
        nextToken();
        return true;
    }
    return false;
}

//  Funcao que passa ao proximo simbolo da cadeia

void nextToken()
{
    pos++;
    lookahead = string[pos];
}

//  Funcao da regra de derivacao 'list'

int list()
{
    if (digit() && listR())
        return true;
    return false;
}

//  Funcao da regra de derivacao 'listR'

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
        return false;
    }
}

//  Funcao da regra de derivacao 'digit'

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
    return false;
}

//  Funcao Principal

int main()
{
    int accept = false;

    printf("Informe uma cadeia: ");
    scanf("%s", string); //  Leitura da Cadeia

    lookahead = string[0];

    accept = list();

    if (accept)
    {
        printf("A Cadeia PERTENCE a linguagem\n");
    }
    else
    {
        printf("A Cadeia NÃO PERTENCE a linguagem\n");
    }

    return 1;
}