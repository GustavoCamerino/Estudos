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
	; Armazenamento de numero
	mov rax,2
	push rax
	; Atribuicao para dummy
	pop rax
	mov dword [dummy], eax
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
	; Leitura de dummy
	mov rdi, fmt_input_int
	mov rsi, dummy
	mov eax, 0
	; Realinha pilha para chamar scanf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call scanf
	; Restaura pilha apos scanf
	mov  rsp, rbp
	pop  rbp
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
	; Carrega variavel 'dummy'
	mov eax, [dummy]
	push rax
	; Atribuicao para a
	pop rax
	mov dword [a], eax
	; Carrega float constante __float_const_0
	movsd xmm0, [__float_const_0]
	movq rax, xmm0
	push rax
	; Atribuicao para b
	pop rax
	movq xmm0, rax
	movq [b], xmm0
	; Armazenamento de caractere
	mov eax, 0x65
	push rax
	; Atribuicao para c
	pop rax
	mov byte [c], al	; Armazena apenas 1 byte (AL = parte baixa de RAX)
	; Chamada de funcao
	call label_func0
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
	; Armazenamento de numero
	mov rax,5
	push rax
	; Atribuicao para n
	pop rax
	mov dword [n], eax
	; Chamada de funcao
	call label_func1
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
	jmp _exit
label_func0:
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
	; Escrita de a
	mov rdi, fmt_output_int
	mov esi, [a]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de b
	mov rdi, fmt_output_float
	movq xmm0, [b]
	mov eax, 1 ; AL contem 1 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 1
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de c
	mov rdi, fmt_output_char
	mov sil, [c]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de str6
	mov rdi, fmt_output_string
	lea rsi, [str6]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de str7
	mov rdi, fmt_output_string
	lea rsi, [str7]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Carrega variavel 'a'
	mov eax, [a]
	push rax
	; Armazenamento de numero
	mov rax,0
	push rax
	;Aplica operador booleano/exp.logica
	pop rbx
	pop rax
	mov rcx,1
	cmp eax,ebx
	jg label_bool0
	mov rcx,0
label_bool0:
	mov rax, rcx
	push rax
	; Jump condicional
	pop rax
	cmp rax, 0
	jz label0
	; Escrita de str8
	mov rdi, fmt_output_string
	lea rsi, [str8]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de str9
	mov rdi, fmt_output_string
	lea rsi, [str9]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Carrega variavel 'a'
	mov eax, [a]
	push rax
	; Atribuicao para n
	pop rax
	mov dword [n], eax
	; Chamada de funcao
	call label_func1
	; Escrita de str10
	mov rdi, fmt_output_string
	lea rsi, [str10]
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
	; Carrega variavel 'a'
	mov eax, [a]
	push rax
	; Armazenamento de numero
	mov rax,0
	push rax
	;Aplica operador booleano/exp.logica
	pop rbx
	pop rax
	mov rcx,1
	cmp eax,ebx
	je label_bool1
	mov rcx,0
label_bool1:
	mov rax, rcx
	push rax
	; Jump condicional
	pop rax
	cmp rax, 0
	jz label2
	; Escrita de str11
	mov rdi, fmt_output_string
	lea rsi, [str11]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de str12
	mov rdi, fmt_output_string
	lea rsi, [str12]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Carrega variavel 'a'
	mov eax, [a]
	push rax
	; Atribuicao para n
	pop rax
	mov dword [n], eax
	; Chamada de funcao
	call label_func1
	; Escrita de str13
	mov rdi, fmt_output_string
	lea rsi, [str13]
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
	jmp label3
label2:
	; Escrita de str14
	mov rdi, fmt_output_string
	lea rsi, [str14]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Escrita de str15
	mov rdi, fmt_output_string
	lea rsi, [str15]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Carrega variavel 'a'
	mov eax, [a]
	push rax
	; Atribuicao para n
	pop rax
	mov dword [n], eax
	; Chamada de funcao
	call label_func1
	; Escrita de str16
	mov rdi, fmt_output_string
	lea rsi, [str16]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
label3:
label1:
	; Retorno de funcao
	ret
label_func1:
	; Escrita de str17
	mov rdi, fmt_output_string
	lea rsi, [str17]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
label4:
	; Carrega variavel 'n'
	mov eax, [n]
	push rax
	; Armazenamento de numero
	mov rax,0
	push rax
	;Aplica operador booleano/exp.logica
	pop rbx
	pop rax
	mov rcx,1
	cmp eax,ebx
	jge label_bool2
	mov rcx,0
label_bool2:
	mov rax, rcx
	push rax
	; Jump condicional
	pop rax
	cmp rax, 0
	jz label5
	; Escrita de n
	mov rdi, fmt_output_int
	mov esi, [n]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Carrega variavel 'n'
	mov eax, [n]
	push rax
	; Armazenamento de numero
	mov rax,1
	push rax
	; Subtracao
	pop rbx
	pop rax
	sub rax,rbx
	push rax
	; Atribuicao para n
	pop rax
	mov dword [n], eax
	; Jump incondicional
	jmp label4
label5:
	; Escrita de str18
	mov rdi, fmt_output_string
	lea rsi, [str18]
	mov eax, 0 ; AL contem 0 vetor de registro -> AL (8 bits menos significativos do eax) eh setado em 0
	; Realinha pilha para chamar printf
	push rbp
	mov  rbp, rsp
	and  rsp, -16
	call printf
	; Restaura pilha apos printf
	mov  rsp, rbp
	pop  rbp
	; Retorno de funcao
	ret

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

str0 db "Inicio da 'main'", 10, 0
str1 db "Escreva um valor:", 10, 0
str2 db "Chamando funcao 'int test(int a, float b, char c)'", 10, 0
str3 db "Voltamos para a 'main'. Contando de 5 ateh 0:", 10, 0
str4 db "Voltamos para a 'main'.", 10, 0
str5 db "Entramos na funcao 'test'. Valor dos parametros passados:", 10, 0
str6 db "", 10, 0
str7 db "Testando se a > 0 (print 1), a == 0 (print 0) ou a < 0 (print -1):", 10, 0
str8 db "'a' MAIOR QUE ZERO -> 1", 10, 0
str9 db "Contando de 'a' ateh zero", 10, 0
str10 db "Voltamos para a funcao 'test'", 10, 0
str11 db "'a' IGUAL A ZERO -> 0", 10, 0
str12 db "Contando de 'a' ateh zero", 10, 0
str13 db "Voltamos para a funcao 'test'", 10, 0
str14 db "'a' MENOR QUE ZERO -> -1", 10, 0
str15 db "Contando de 'a' ateh zero (nao vai contar, pois 'a' eh negativo)", 10, 0
str16 db "Voltamos para a funcao 'test'", 10, 0
str17 db "Chegamos na funcao 'countdown'", 10, 0
str18 db "FIM DA CONTAGEM!", 10, 0

; Float Constantes
__float_const_0 dq 2.213

section .bss
dummy resd 1 ; 4 bytes
a resd 1 ; 4 bytes
b resq 1 ; 8 bytes
c resd 1 ; 4 bytes
n resd 1 ; 4 bytes
