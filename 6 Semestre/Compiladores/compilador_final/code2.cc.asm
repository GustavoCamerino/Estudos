;UFMT-Compiladores
;Prof. Ivairton
;Procedimento para geracao do executavel apos compilacao (em Linux):
;(1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>
;(2) likedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>

extern printf
extern scanf
extern exit


section .text
	global main,_start

main:
_start:
	; Escrita de str0
	mov rdi, fmt_output_string
	lea rsi, [str0]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Armazenamento de numero
	mov rax,1
	push rax
	; Armazenamento de numero
	mov rax,1
	push rax
	; Subtracao
	pop rbx
	pop rax
	sub rax,rbx
	push rax
	; Jump condicional
	pop rax
	cmp rax, 0
	jz label0
	; Escrita de str1
	mov rdi, fmt_output_string
	lea rsi, [str1]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Jump incondicional
	jmp label1
label0:
	; Escrita de str2
	mov rdi, fmt_output_string
	lea rsi, [str2]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
label1:
	; Escrita de str3
	mov rdi, fmt_output_string
	lea rsi, [str3]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Leitura de valor
	mov rdi, fmt_input_int
	mov rsi, valor
	mov eax, 0
	; Realinha pilha para chamar scanf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call scanf
	; Restaura pilha apos scanf
	mov  rsp, rbp
	pop  rbp
	; Escrita de str4
	mov rdi, fmt_output_string
	lea rsi, [str4]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de str5
	mov rdi, fmt_output_string
	lea rsi, [str5]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
label2:
	; Carrega variavel 'valor'
	mov eax, [valor]
	push rax
	; Armazenamento de numero
	mov rax,10
	push rax
	;Aplica operador booleano/exp.logica
	pop rbx
	pop rax
	mov rcx,1
	cmp eax,ebx
	jle label_bool0
	mov rcx,0
label_bool0:
	mov rax, rcx
	push rax
	; Jump condicional
	pop rax
	cmp rax, 0
	jz label3
	; Escrita de valor
	mov rdi, fmt_output_int
	mov esi, [valor]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Carrega variavel 'valor'
	mov eax, [valor]
	push rax
	; Armazenamento de numero
	mov rax,1
	push rax
	; Adicao
	pop rax
	pop rbx
	add rax,rbx
	push rax
	; Atribuicao para valor
	pop rax
	mov dword [valor], eax
	; Jump incondicional
	jmp label2
label3:
	jmp _exit

_exit:
	; Encerra o programa
	mov ebx,0
	mov eax,1
	int 0x80

section .data
fmt_input_int db "%d", 0
fmt_output_int db "%d", 10, 0
fmt_input_float db "%lf", 0
fmt_output_float db "%lf", 10, 0
fmt_input_string db "%s", 0
fmt_output_string db "%s", 10, 0
fmt_input_char db "%c", 0
fmt_output_char db "%c", 10, 0

str0 db "Calculando 1 - 1 = 0 -> falso", 10, 0
str1 db "O valor do teste eh VERDADEIRO!\n", 10, 0
str2 db "O valor eh teste eh FALSO!\n", 10, 0
str3 db "Informe um valor menor ou igual a dez:", 10, 0
str4 db "", 10, 0
str5 db "Escrevendo de 'valor' ateh 10", 10, 0


section .bss
valor resd 1 ; 4 bytes
