/**
 * @file gen.c
 * @author Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo gerador de codigo
 * @version 0.3
 * @date 2022-02-23
 */

#include "gen.h"

extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
char output_file_name[MAX_CHAR];
FILE *output_file;

void genAdd() {
    fprintf(output_file, "; Adicao\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tadd rax, rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

void genSub() {
    fprintf(output_file, "; Subtracao\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tsub rax, rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

void genMult() {
    fprintf(output_file, "; Multiplicacao\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\timul rax, rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

void genDiv() {
    fprintf(output_file, "; Divisao\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tidiv rax, rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

void genNum(char num_string[MAX_TOKEN]) {
    fprintf(output_file, "; Armazenamento de numero\n");
    fprintf(output_file, "\tmov rax, %s\n", num_string);
    fprintf(output_file, "\tpush rax\n");
}

void gen_push_var(char *var_name) {
    fprintf(output_file, "; Empilha variavel\n");
    fprintf(output_file, "\tmov rax, [%s]\n", var_name);
    fprintf(output_file, "\tpush rax\n");
}

void gen_preambule(void) {
    fprintf(output_file, "; UFMT-Compiladores\n");
    fprintf(output_file, "; Prof. Ivairton\n");
    fprintf(output_file, "; Procedimento para geracao do executavel apos compilacao (em Linux):\n");
    fprintf(output_file, "; (1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>\n");
    fprintf(output_file, "; (2) linkedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>\n\n");
    fprintf(output_file, "extern printf\n");
    fprintf(output_file, "extern scanf\n");
}

void gen_data_section(void) {
    int i, n;
    
    fprintf(output_file, "\n\tsection .data\n");

    n = global_symbol_table_variables.n_variables;
    for (i = 0; i < n; i++) {
       fprintf(output_file, "%s: ", global_symbol_table_variables.variable[i].name); 
       
       switch(global_symbol_table_variables.variable[i].type) {
            case INT:
                fprintf(output_file, "dd 0\n");
                break;
            case STRING:
                fprintf(output_file, "db \"                \", 0\n");
                break;
            case FLOAT:
                fprintf(output_file, "dq 0.0\n");
                break;
            case CHAR:
                fprintf(output_file, "db 0\n");
                break;
            default:
                fprintf(output_file, "[ERRO] Tipo desconhecido.\n");       
                break;           
       }
    }

    n = symbol_table_string.n_strings;
    for (i = 0; i < n; i++) {
        fprintf(output_file, "%s: db %s, 0\n",
            symbol_table_string.string[i].name, 
            symbol_table_string.string[i].value);
    }
}

void gen_preambule_code(void) {
    fprintf(output_file, "\n\tsection .text\n");
    fprintf(output_file, "\tglobal main,_start\n");
    fprintf(output_file, "main:\n");
    fprintf(output_file, "_start:\n");
}

void gen_epilog_code(void) {
    fprintf(output_file, "\n; Encerra programa\n");
    fprintf(output_file, "\tmov ebx, 0\n");
    fprintf(output_file, "\tmov eax, 1\n");
    fprintf(output_file, "\tint 0x80\n");
}

void gen_label_name(char *name) {
    char str_name[MAX_CHAR];
    char conv_value[16];
    static int nlabels = 0;

    sprintf(conv_value, "%d", nlabels);
    strcpy(str_name, "label");
    strcat(str_name, conv_value);
    strcpy(name, str_name);
    nlabels++;
}

void gen_label(char *label) {
    fprintf(output_file, "%s:\n", label);
}

void gen_cond_jump(char *label) {
    fprintf(output_file, "; Jump condicional\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tcmp rax, 0\n");
    fprintf(output_file, "\tjz %s\n", label);
}

void gen_incond_jump(char *label) {
    fprintf(output_file, "; Jump incondicional\n");
    fprintf(output_file, "\tjmp %s\n", label);
}

void gen_bool(int oper) {
    char bool_label_name[MAX_CHAR];
    fprintf(output_file, "; Aplica operador booleano/exp.logica\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tpop rax\n");
    gen_bool_label_name(bool_label_name);
    fprintf(output_file, "\tmov rcx, 1\n");
    fprintf(output_file, "\tcmp rax, rbx\n");
    switch (oper) {
        case EQUAL:
            fprintf(output_file, "\tje %s\n", bool_label_name);
            break;
        case NE:
            fprintf(output_file, "\tjne %s\n", bool_label_name);
            break;
        case LT:
            fprintf(output_file, "\tjl %s\n", bool_label_name);
            break;
        case GT:
            fprintf(output_file, "\tjg %s\n", bool_label_name);
            break;
        case LE:
            fprintf(output_file, "\tjle %s\n", bool_label_name);
            break;
        case GE:
            fprintf(output_file, "\tjge %s\n", bool_label_name);
            break;
        default:
            printf("[ERRO] Operador booleano nao suportado.\n");
            break;
    }
    fprintf(output_file, "\tmov rcx, 0\n");
    gen_label(bool_label_name);
    fprintf(output_file, "\tmov rax, rcx\n");
    fprintf(output_file, "\tpush rax\n");
}

void gen_bool_label_name(char *name) {
    char conv_value[16];
    static int nbool_labels = 0;
    sprintf(conv_value, "%d", nbool_labels);
    strcpy(name, "label_bool");
    strcat(name, conv_value);
    nbool_labels++;
}

void gen_read(char *lexeme_of_id, int type) {
    switch (type) {
        case INT:
            fprintf(output_file, "\n; Le valor inteiro\n");
            fprintf(output_file, "\tmov edx, 4\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 3\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
        case FLOAT:
            fprintf(output_file, "\n; Le valor float\n");
            fprintf(output_file, "\tmov edx, 16\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 3\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
        case CHAR:
            fprintf(output_file, "\n; Le valor char\n");
            fprintf(output_file, "\tmov edx, 1\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 3\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
        case STRING:
            fprintf(output_file, "\n; Le valor string\n");
            fprintf(output_file, "\tmov edx, 16\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 3\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
    }
}

void gen_write(char *lexeme_of_id, int type) {
    switch (type) {
        case INT:
            fprintf(output_file, "\n; Escreve valor inteiro\n");
            fprintf(output_file, "\tmov edx, 4\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 4\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
        case FLOAT:
            fprintf(output_file, "\n; Escreve valor float\n");
            fprintf(output_file, "\tmov edx, 16\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 4\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
        case CHAR:
            fprintf(output_file, "\n; Escreve valor char\n");
            fprintf(output_file, "\tmov edx, 1\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 4\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
        case STRING:
            fprintf(output_file, "\n; Escreve valor string\n");
            fprintf(output_file, "\tmov edx, 16\n");
            fprintf(output_file, "\tmov ecx, %s\n", lexeme_of_id);
            fprintf(output_file, "\tmov ebx, 1\n");
            fprintf(output_file, "\tmov eax, 4\n");
            fprintf(output_file, "\tint 0x80\n");
            break;
    }
}