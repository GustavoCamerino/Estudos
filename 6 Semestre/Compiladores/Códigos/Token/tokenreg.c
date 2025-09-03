#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAX_CHAR 32
#define true 1
#define false 0
#define ERROR -1

// Regras e simbolos da gramatica
#define E 0
#define ER 1
#define T 2
#define TR 3
#define F 4
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
int reg_counter = 0; // Contador de registradores
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
void driver();

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

// Geração de código: atribui um novo registrador
void generate_code(char *operation, int reg1, int reg2)
{
    printf("    %s R%d, R%d\n", operation, reg1, reg2);
}

// Geração de código para um operando imediato (número)
void load_immediate(int reg, int value)
{
    printf("    MOV R%d, #%d\n", reg, value);
}

// Funcao da regra de derivacao 'digit'
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
        // Adição de comando para geração de código:
        load_immediate(reg_counter, ch - '0'); // Carrega o valor no registrador
        reg_counter++;                         // Incrementa o contador de registradores
        return true;
    }
    return false;
}

void driver()
{
    push(end); // Empilha o marcador de fim de entrada ($)
    push(E);   // Empilha o símbolo não-terminal inicial (E)

    lookahead = string[pos]; // Inicializa o lookahead com o primeiro símbolo de entrada

    while (stack.count > 0)
    {
        int X = pop(); // Desempilha o topo da pilha

        if (X == end)
        {
            if (lookahead == '\0') // Verifica se chegou ao fim da entrada
            {
                printf("Aceito!\n");
                return;
            }
            else
            {
                printf("Erro!\n");
                return;
            }
        }
        else if (X >= id && X <= end) // Se X for um terminal
        {
            if (match(X)) // Verifica se o terminal bate com o lookahead
            {
                nextToken();
            }
            else
            {
                printf("Erro!\n");
                return;
            }
        }
        else if (TAS[X][lookahead].ruler[0] != ERROR) // Se X for um não-terminal e tiver uma regra na TAS
        {
            typeArrayInt rule = TAS[X][lookahead];
            for (int i = MAX_CHAR - 1; i >= 0; i--) // Empilha a produção na ordem inversa
            {
                if (rule.ruler[i] != empty)
                {
                    push(rule.ruler[i]);
                }
            }
        }
        else // Erro sintático
        {
            printf("Erro!\n");
            return;
        }
    }
}

// Funcao principal
int main()
{
    stack.count = 0; // Inicialização do contador da pilha
    push(end);
    push(E);

    int acept = false;

    printf("Informe uma cadeia:");
    // scanf("%s", string); //leitura da cadeia
    strcpy(string, "2+3");

    lookahead = string[0]; // inicialização do lookahead

    acept = E(); // Chamada da derivação/funcao inicial da gramática

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
