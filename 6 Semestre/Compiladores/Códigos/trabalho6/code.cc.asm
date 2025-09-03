extern printf
extern scanf
extern exit

section .data
  fmt_i_str0 db "%d", 0
  fmt_o_str0 db "%d",10,0
  ;a: dd 0

section .bss
  a resd 1

section .text
  global main

main:
  mov rdi, fmt_i_str0
  lea rsi, [a]
  xor eax, eax
  call scanf

  mov rdi, fmt_o_str0
  mov esi, [a]
  xor eax, eax
  call printf

.exit:
  mov rdi, 0
  call exit
