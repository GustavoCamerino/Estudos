/**
 * @file symbols.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo do gerador da tabela de simbolos
 * @version 0.1
 * @date 2022-02-04
 */
#include "symbols.h"
#include "gen.h"

//extern int nstringconsts;
//int sympos = 0;
//int nstringconsts = 0;
//int symfuncspos = 0; //Sera usado posteriormente
//int stack_pos = 0;

//Variaveis globais
type_symbol_table_variables global_symbol_table_variables;
type_symbol_table_string symbol_table_string;
FloatConstant float_constants[MAX_FLOAT];
int float_const_count = 0;

// Tabela de funcoes
type_symbol_function_entry symfuncs[MAX_FUNCS]; 
int symfuncspos = 0; 

/**
 * @brief Busca pelo simbolo na tabela de variaveis
 * 
 * @param char*
 * @param type_symbol_table_variables*
 * @return type_symbol_table_entry* 
 */
type_symbol_table_entry *sym_find(char *s, type_symbol_table_variables *stv) {
	int i;
	type_symbol_table_entry *symbol = NULL;
	for (i = 0; i < stv->n_variables; i++) {
		if (strcmp(stv->variable[i].name, s) == 0) {
			symbol = &(stv->variable[i]);
		}
	}
	return symbol;
}

/**
 * @brief Insere um novo simbolo na tabela de variaveis
 * 
 * @param name 
 * @param type 
 * @param addr 
 * @return type_symbol* 
 */
 type_symbol_table_entry *sym_declare(char *name, int type, int addr, type_symbol_table_variables *stv) {
	if (stv->n_variables < MAX_SYMBOLS) { //Verifica se eh possivel declarar mais variavel
		int n_var;
        n_var = stv->n_variables;
        stv->variable[n_var].type = type;
        stv->variable[n_var].addr = addr;
        strcpy(stv->variable[n_var].name, name);
        stv->n_variables++;
        n_var = stv->n_variables;
        return &(stv->variable[n_var]);
	} else {
        printf("[ERRO] Limite de declaracao (quantidade) de variaveis atingido.\n");
        return NULL;
    }
}

/**
 * @brief Busca pelo simbolo na tabela de STRINGS
 * 
 * @param char*
 * @return type_symbol_table_string_entry* 
 */
type_symbol_table_string_entry *sym_string_find(char *s) {
    int i;
    type_symbol_table_string_entry *str = NULL;
    for (i = 0; i < symbol_table_string.n_strings; i++ ) {
        if ( strcmp(symbol_table_string.string[i].value, s) == 0 ) {
            str = &(symbol_table_string.string[i]);
        }
    }
    return str;
}

/**
 * @brief Insere um novo simbolo na tabela de STRINGS
 * 
 * @param char*
 * @return type_symbol_table_string_entry* 
 */
type_symbol_table_string_entry *sym_string_declare(char *s) {
    static int str_label_count = 0;

    if ( symbol_table_string.n_strings < MAX_SYMBOLS ) {
        int n_str;
        char str_name[MAX_TOKSZ];
        sprintf(str_name, "str%d", str_label_count);
        n_str = symbol_table_string.n_strings;

        strcpy(symbol_table_string.string[n_str].value, s);
        strcpy(symbol_table_string.string[n_str].name, str_name);
        str_label_count++;
        symbol_table_string.n_strings++;
        return &(symbol_table_string.string[n_str]) ;
    } else {
        printf("[ERRO] Numero maximo de strings declaradas alcancado!\n");
        return NULL;
    }
}

/**
 * @brief Busca pelo simbolo na tabela (funcoes)
 * 
 * @param s 
 * @return type_symbol_function* 
 * 
 * @note Funcao modificada para parar no momento que encontrar a funcao "s" pelo nome
 */
type_symbol_function_entry *sym_func_find(char *s){
	for (int i = 0; i < symfuncspos; i++) {
		if (strcmp(symfuncs[i].name, s) == 0) {
			return &symfuncs[i]; // Encontrou a funcao
		}
	}
	return NULL; // Nao encontrou a funcao
}


/**
 * @brief Insere um novo simbolo na tabela (funcoes)
 * 
 * @param name 
 * @param type 
 * @param params 
 * @param nparams 
 * @return type_symbol_function* 
 * 
 * @note Algumas alteracoes foram feitas na versao original para essa modificada:
 * - A versao original verificava se o limite de funcoes foi passada apos apos incrementar, agora verifica antes de inserir.
 * - A versao original nao retornava erro imediatamente se o limite de funcoes fosse atingido, agora retorna "NULL" imediatamente.
 * - O Parametro "type" foi alteado de 'char' para 'int', pois os tipos sao definidos como constantes inteiras
 */
type_symbol_function_entry *sym_func_declare(char *name, int type, type_symbol_table_entry params[MAX_PARAMS], int nparams) {
    // verifica se o limite de funcoes foi atingido
    if (symfuncspos >= MAX_FUNCS) {
        printf("[ERRO] Limite de funcoes atingido.\n");
        return NULL;
    }

    type_symbol_function_entry *entry = &symfuncs[symfuncspos];
    entry->type = type;
    strncpy(entry->name, name, MAX_TOKSZ);
    entry->nparams = nparams;

    for (int i = 0; i < nparams; i++) {
        strncpy(entry->params[i].name, params[i].name, MAX_TOKSZ); // Copia nome
        entry->params[i].type = params[i].type; // Copia tipo
    }

    symfuncspos++;

    // Gera a label para a funcao
    gen_func_label_name(entry->label);

    return entry;
}

/**
 * @brief Inicializa tabela de simbolos de variaveis globais
 * 
 * @param stv 
 */
void initSymbolTableVariables(type_symbol_table_variables *stv) {
    int i;
    stv->n_variables = 0;
    for (i = 0; i < MAX_SYMBOLS; i++) {
        strcpy(stv->variable[i].name, "");
        stv->variable[i].type = -1;
        stv->variable[i].addr = 0;
    }
    stv->next = NULL;
}

/**
 * @brief Inicializa tabela de simbolos de strings
 * 
 */
void initSymbolTableString() {
    int i;
    symbol_table_string.n_strings = 0;
    for (i = 0; i < MAX_SYMBOLS; i++) {
        strcpy(symbol_table_string.string[i].name, "");
        strcpy(symbol_table_string.string[i].value, "");
    }
}

///Para DEBUG
// Imprime a tabela de simbolos de variaveis
void printSTVariables(type_symbol_table_variables *stv) {
    int i, n_var;
    printf("TABELA DE SIMBOLOS DE VARIAVEIS:\n");
    n_var = stv->n_variables;
    printf("Numero de variaveis = %d\n", n_var);
    for (i = 0; i < n_var; i++) {
        printf("\tvariavel[%d].name:%s\n", i, stv->variable[i].name);
        printf("\tvariavel[%d].type:%d\n", i, stv->variable[i].type);
    }
}

// Imprime a tabela de simbolos de strings
void printSTString() {
    int i, n_str;
    printf("TABELA DE SIMBOLOS DE STRINGS:\n");
    n_str = symbol_table_string.n_strings;
    printf("Numero de strings = %d\n", n_str);
    for (i = 0; i < n_str; i++) {
        printf("\tstring[%d].name:%s\n", i, symbol_table_string.string[i].name);
        printf("\tstring[%d].value:%s\n", i, symbol_table_string.string[i].value);
    }
}

// Imprime a tabela de simbolos de funcoes
void printSTFunctions() {
    printf("TABELA DE SIMBOLOS DE FUNCOES:\n");
    for (int i = 0; i < symfuncspos; i++) {
        printf("Funcao: %s\n", symfuncs[i].name);
        printf("Tipo de retorno: %d\n", symfuncs[i].type);
        printf("Label (%s):\n", symfuncs[i].label);
        printf("Parametros (%d):\n", symfuncs[i].nparams);
        for (int j = 0; j < symfuncs[i].nparams; j++) {
            printf("  %s (tipo %d)\n", symfuncs[i].params[j].name, symfuncs[i].params[j].type);
        }
        printf("\n");
    }
}