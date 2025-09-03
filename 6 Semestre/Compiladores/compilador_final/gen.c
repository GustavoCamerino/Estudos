/**
 * @file gen.c
 * @author Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo gerador de codigo
 * @version 0.2
 * @date 2022-02-23
 * 
 */

// Inclusao do cabecalho
#include "gen.h"

// Inclusao explicita de variaveis globais de outro contexto (symbols.h)
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
char output_file_name[MAX_CHAR];
FILE *output_file;
extern FloatConstant float_constants[MAX_FLOAT];
extern int float_const_count;


/**
 * @brief Funcao que gera codigo de montagem para SOMA
 * 
 */
void genAdd() {
    fprintf(output_file, "\t; Adicao\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tadd rax,rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para SUBTRACAO
 * 
 */
void genSub() {
    fprintf(output_file, "\t; Subtracao\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tsub rax,rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para valores NEGATIVOS UNARIOS (ex.: -1)
 * @param type Tipo do valor (INT ou FLOAT)
 */
void genNeg(int type) {
    if (type == INT) {
        // Negação para inteiros
        fprintf(output_file, "\tpop rax\n");
        fprintf(output_file, "\tneg rax\n");
        fprintf(output_file, "\tpush rax\n");
    } else if (type == FLOAT) {
        // Negação para floats (usando SSE)
        fprintf(output_file, "\tmovq xmm0, [rsp]\n");
        fprintf(output_file, "\tpxor xmm1, xmm1\n");
        fprintf(output_file, "\tsubsd xmm1, xmm0\t; xmm1 = 0.0 - xmm0\n"); 
        fprintf(output_file, "\tmovq [rsp], xmm1\n");
    }
}

/**
 * @brief Funcao que gera codigo de montagem para MULTIPLICACAO
 * 
 */
void genMult() {
    fprintf(output_file, "\t; Multiplicacao\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\timul rax,rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para DIVISAO
 * 
 */
void genDiv() {
    fprintf(output_file, "\t; Divisao\n");
    fprintf(output_file, "\tpop rbx\t; Divisor\n");
    fprintf(output_file, "\tpop rax\t; Dividendo\n");
    fprintf(output_file, "\tcqo\t; Estende sinal de RAX para RDX:RAX (64 + 64 = 128 bits)\n");
    fprintf(output_file, "\tidiv rbx\t; Divide RDX:RAX por RBX, resultando em RAX (quociente)\n\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento de NUMERAL
 * 
 * @param num_string 
 */
void genNum(char num_string[MAX_TOKEN]) {
    fprintf(output_file, "\t; Armazenamento de numero\n");
    fprintf(output_file, "\tmov rax,%s\n", num_string);
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento de float (NUMERAL)
 */
void genFloat(char *label) {
    fprintf(output_file, "\t; Carrega float constante %s\n", label);
    fprintf(output_file, "\tmovsd xmm0, [%s]\n", label);
    fprintf(output_file, "\tmovq rax, xmm0\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento de caractere (CHARACTER_LITERAL)
 */
void genChar(char c) {
    fprintf(output_file, "\t; Armazenamento de caractere\n");

    // Exemplo: mov eax, 0x61 (para 'a')
    fprintf(output_file, "\tmov eax, 0x%02x\n", (unsigned char)c);
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento de String
 */
void genString(char *label) {
    fprintf(output_file, "\tlea rax, [%s]\n", label);
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento de ID (empilha variavel na memoria)
 * 
 * @param id
 */
void gen_id(char *id) {
    fprintf(output_file, "\t; Carrega variavel '%s'\n", id);
    fprintf(output_file, "\tmov eax, [%s]\n", id); // Carrega valor da variável
    fprintf(output_file, "\tpush rax\n");           // Empilha o valor
}

/**
 * @brief Funcao que gera um preambulo que permite o uso das funcoes do C (scanf e printf)
 * 
 */
void gen_preambule(void) {
    fprintf(output_file, ";UFMT-Compiladores\n");
    fprintf(output_file, ";Prof. Ivairton\n");
    fprintf(output_file, ";Procedimento para geracao do executavel apos compilacao (em Linux):\n");
    fprintf(output_file, ";(1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>\n");
    fprintf(output_file, ";(2) likedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>\n\n");
    fprintf(output_file, "extern printf\n");
    fprintf(output_file, "extern scanf\n");
    fprintf(output_file, "extern exit\n\n");
}

/**
 * @brief Funcao que gera codigo da secao de dados (declaracao de variaveis).
 */
void gen_data_section(void) {
    int i, n;
    
    // Secao .data para strings e formatos
    fprintf(output_file, "\nsection .data\n");
    fprintf(output_file, "fmt_input_int db \"%%d\", 0\n");
    fprintf(output_file, "fmt_output_int db \"%%d\", 10, 0\n");

    fprintf(output_file, "fmt_input_float db \"%%lf\", 0\n");
    fprintf(output_file, "fmt_output_float db \"%%lf\", 10, 0\n");

    fprintf(output_file, "fmt_input_string db \"%%s\", 0\n");
    fprintf(output_file, "fmt_output_string db \"%%s\", 10, 0\n");

    fprintf(output_file, "fmt_input_char db \"%%c\", 0\n");
    fprintf(output_file, "fmt_output_char db \"%%c\", 10, 0\n\n");

    // Strings do programa
    n = symbol_table_string.n_strings;
    for (i = 0; i < n; i++) {
        fprintf(output_file, "str%d db %s, 10, 0\n", i, symbol_table_string.string[i].value);
    }

    // Se tiver alguma string para armazenar, quebra linha ao final dela. Apenas para melhor estetica do assembly
    if (n != 0) {
        fprintf(output_file, "\n");
    }

    // Adiciona as constantes Floats
    if (float_const_count > 0) {
        fprintf(output_file, "; Float Constantes\n");
        for (i = 0; i < float_const_count; i++) {
            fprintf(output_file, "%s dq %s\n", float_constants[i].label, float_constants[i].value);
        }
    }


    // Seção .bss para variáveis
    fprintf(output_file, "\nsection .bss\n");
    // processa cada simbolo da tabela e gera um ponteiro para cada variavel na memoria
    n = global_symbol_table_variables.n_variables;
    for (i = 0; i < n; i++) {
        if (global_symbol_table_variables.variable[i].type == FLOAT) {
            fprintf(output_file, "%s resq 1 ; 8 bytes\n", global_symbol_table_variables.variable[i].name);
        

        
        } else if(global_symbol_table_variables.variable[i].type == STRING) {
            fprintf(output_file, "%s resb %d ; %d bytes (para String)\n", global_symbol_table_variables.variable[i].name, MAX_CHAR, MAX_CHAR);

        } else {
            fprintf(output_file, "%s resd 1 ; 4 bytes\n", global_symbol_table_variables.variable[i].name);
        }
    }
}

/**
 * @brief Funcao que gera a marcacao do inicio da secao de codigo
 * 
 */
void gen_preambule_code(void) {
    fprintf(output_file, "\nsection .text\n");
    fprintf(output_file, "\tglobal main,_start\n\n");
    fprintf(output_file, "main:\n");
    fprintf(output_file, "_start:\n");
}

/**
 * @brief Funcao que encerra o codigo inserindo comandos de fechamento
 * 
 */
void gen_epilog_code(void) {
    //fprintf(output_file, "\nret\n");
    // Gera um label para o fim do programa
    fprintf(output_file, "\n_exit:");

    // Encerra o programa
    fprintf(output_file, "\n\t; Encerra o programa\n");
    fprintf(output_file, "\tmov ebx,0\n");
    fprintf(output_file, "\tmov eax,1\n");
    fprintf(output_file, "\tint 0x80\n");
}

/**
 * @brief Funcao que gera jump para o fim do programa
 * @details Essa funcao eh chamada no fim do codigo principal do bloco "begin"/"end",
 * para que o assembly nao rode as implementacoes das funcoes, a menos que seja feita uma chamada daquela funcao no bloco principal
 */
void gen_jump_exit() {
    fprintf(output_file, "\tjmp _exit\n"); // _exit eh o label do final do programa
}

/**
 * @brief Funcao que gera automaticamente um novo nome para um label
 * @param string name
 */
void gen_label_name( char *name ) {
    char str_name[MAX_CHAR];
    char conv_value[16];
    static int nlabels=0;

    sprintf(conv_value, "%d", nlabels);
    strcpy(str_name, "label");
    strcat(str_name, conv_value);
    strcpy(name, str_name);
    nlabels++;
}

/**
 * @brief Funcao que gera automaticamente um novo nome para um label de uma funcao
 * @param string name
 */
void gen_func_label_name(char *name) {
    char str_name[MAX_CHAR];
    char conv_value[16];
    static int nlabels_func=0;

    sprintf(conv_value, "%d", nlabels_func);
    strcpy(str_name, "label_func");
    strcat(str_name, conv_value);
    strcpy(name, str_name);
    nlabels_func++;
}

/**
 * @brief Funcao que registra no codigo um label
 * @param string label 
 */
void gen_label( char *label ) {
    fprintf(output_file, "%s:\n", label);
}

/**
 * @brief Funcao que gera um jump condicional
 * @param string label
 */
void gen_cond_jump(char *label) {
    fprintf(output_file, "\t; Jump condicional\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tcmp rax, 0\n");
    fprintf(output_file, "\tjz %s\n", label);
}

/**
 * @brief Funcao que gera um jump incondicional
 * @param string label
 */
void gen_incond_jump(char *label) {
    fprintf(output_file, "\t; Jump incondicional\n");
    fprintf(output_file, "\tjmp %s\n", label);
}

/**
 * @brief Gera codigo de montagem para salto para o inicio da funcao (call)
 * @param label Label da funcao
 */
void gen_call(char *label) {
    fprintf(output_file, "\t; Chamada de funcao\n");
    fprintf(output_file, "\tcall %s\n", label);
}

/**
 * @brief Gera codigo de retorno de funcao
 */
void gen_ret() {
    fprintf(output_file, "\t; Retorno de funcao\n");
    fprintf(output_file, "\tret\n");
}

/**
 * @brief Funcao que gera codigo a partir do processamento da expressao logica
 * 
 * @param oper 
 */
void gen_bool(int oper) {
    static int bool_label;
    char bool_label_name[MAX_CHAR];
    fprintf(output_file,"\t;Aplica operador booleano/exp.logica\n");
    fprintf(output_file,"\tpop rbx\n");
    fprintf(output_file,"\tpop rax\n");
    gen_bool_label_name(bool_label_name);
    fprintf(output_file,"\tmov rcx,1\n");
    fprintf(output_file,"\tcmp eax,ebx\n");
    switch (oper) {
        case EQUAL:
            fprintf(output_file,"\tje %s\n", bool_label_name);
            break;
        case NE:
            fprintf(output_file,"\tjne %s\n",bool_label_name);
            break;
        case LT:
            fprintf(output_file,"\tjl %s\n", bool_label_name);
            break;
        case GT:
            fprintf(output_file,"\tjg %s\n", bool_label_name);
            break;
        case LE:
            fprintf(output_file,"\tjle %s\n", bool_label_name);
            break;
        case GE:
            fprintf(output_file,"\tjge %s\n", bool_label_name);
            break;
        default:
            printf("[ERRO] operador booleano nao suportado.\n");
            break;
    }
    fprintf(output_file, "\tmov rcx,0\n");
    gen_label(bool_label_name);
    fprintf(output_file, "\tmov rax, rcx\n");
    fprintf(output_file, "\tpush rax\n");
}


void gen_bool_label_name(char *name) {
    char str_name[MAX_CHAR];
    char conv_value[16];
    static int nbool_labels = 0;
    
    // Usando um prefixo fixo em vez do parametro de entrada
    strcpy(str_name, "label_bool");
    
    sprintf(conv_value, "%d", nbool_labels);
    strcat(str_name, conv_value);
    
    strcpy(name, str_name); // Copia o nome gerado para o parâmetro de saída
    nbool_labels++;
}

// Gera codigo assembly para operador "&&"
void gen_logical_and() {
    fprintf(output_file, "\t; AND logico\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tand rax, rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

// Gera codigo assembly para operador "||"
void gen_logical_or() {
    fprintf(output_file, "\t; OR logico\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tor rax, rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

// Gera codigo assembly para atribuicao "="
void gen_assign(char *var_name, int type) {
    fprintf(output_file, "\t; Atribuicao para %s\n", var_name);
    fprintf(output_file, "\tpop rax\n");
    
    switch (type) {
        case INT:
            fprintf(output_file, "\tmov dword [%s], eax\n", var_name);
            break;
        
        case FLOAT:
            fprintf(output_file, "\tmovq xmm0, rax\n");
            fprintf(output_file, "\tmovq [%s], xmm0\n", var_name);
            
            break;
        
        case CHAR:
            // Armazena apenas 1 byte (AL = parte baixa de RAX)
            fprintf(output_file, "\tmov byte [%s], al\t; Armazena apenas 1 byte (AL = parte baixa de RAX)\n", var_name);
            break;
        
        case STRING:
        fprintf(output_file, "\tmov [%s], rax\n", var_name); // Armazena endereco da string
            break;
        
        default:
            fprintf(output_file, "\tmov dword [%s], eax\n", var_name);
            break;
    }
}

/**
 * @brief Gera codigo para o comando READ
 * 
 * @param lexeme_of_id nome do identificador
 */
void gen_read(char *lexeme_of_id, int type) {
    fprintf(output_file, "\t; Leitura de %s\n", lexeme_of_id);
    switch (type) {
        case INT:
            fprintf(output_file, "\tmov rdi, fmt_input_int\n");
            fprintf(output_file, "\tmov rsi, %s\n", lexeme_of_id);
            break;
        case FLOAT:
            fprintf(output_file, "\tmov rdi, fmt_input_float\n");
            fprintf(output_file, "\tmov rsi, %s\n", lexeme_of_id);
            break;
        case CHAR:
            fprintf(output_file, "\tmov rdi, fmt_input_char\n");
            fprintf(output_file, "\tmov rsi, %s\n", lexeme_of_id);
            break;
        case STRING:
            fprintf(output_file, "\tmov rdi, fmt_input_string\n");
            fprintf(output_file, "\tmov rsi, [%s]\n", lexeme_of_id);
            break;
    }
    fprintf(output_file, "\tmov eax, 0\n");

    fprintf(output_file, "\t; Realinha pilha para chamar scanf\n");
    fprintf(output_file, "\tpush rbp\n");
    fprintf(output_file, "\tmov  rbp, rsp\n");
    fprintf(output_file, "\tand  rsp, -16\n");

    fprintf(output_file, "\tcall scanf\n");

    fprintf(output_file, "\t; Restaura pilha apos scanf\n");
    fprintf(output_file, "\tmov  rsp, rbp\n");
    fprintf(output_file, "\tpop  rbp\n");
}

/**
 * @brief Gera codigo para o comando WRITE
 * 
 * @param lexeme_of_id nome do identificador
 */
void gen_write(char *lexeme_of_id, int type) {
    fprintf(output_file, "\t; Escrita de %s\n", lexeme_of_id);
    switch (type) {
        case INT:
            fprintf(output_file, "\tmov rdi, fmt_output_int\n");
            fprintf(output_file, "\tmov esi, [%s]\n", lexeme_of_id);
            break;
        case FLOAT:
            fprintf(output_file, "\tmov rdi, fmt_output_float\n");
            // 1 registro XMM usado
            fprintf(output_file, "\tmovq xmm0, [%s]\n", lexeme_of_id);
            fprintf(output_file, "\tmov eax, 1 ; AL contem 1 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 1\n");
            break;
        case CHAR:
            fprintf(output_file, "\tmov rdi, fmt_output_char\n");
            fprintf(output_file, "\tmov sil, [%s]\n", lexeme_of_id);
            break;
        case STRING:
            fprintf(output_file, "\tmov rdi, fmt_output_string\n");
            fprintf(output_file, "\tlea rsi, [%s]\n", lexeme_of_id);
            break;
    }

    // Se o tipo nao for float, seta eax para zero
    if (type != FLOAT) {
        fprintf(output_file, "\tmov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0\n");
    }
    

    fprintf(output_file, "\t; Realinha pilha para chamar printf\n");
    fprintf(output_file, "\tpush rbp\n");
    fprintf(output_file, "\tmov  rbp, rsp\n");
    fprintf(output_file, "\tand  rsp, -16\n");
    
    fprintf(output_file, "\tcall printf\n");
    
    fprintf(output_file, "\t; Restaura pilha apos printf\n");
    fprintf(output_file, "\tmov  rsp, rbp\n");
    fprintf(output_file, "\tpop  rbp\n");
}