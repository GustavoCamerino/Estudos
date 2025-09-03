extern printf
extern scanf

section .data
fmtstr0 db "%d", 0
a: dd 0
b: dd 0

section .text
  global main
main:
mov rdi, fmtstr0
mov rsi, a
mov rax, 0
call scanf
mov rdi, fmtstr0
mov rsi, [rel a]
mov rax, 0
call printf
ret
