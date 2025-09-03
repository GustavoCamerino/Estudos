.text 
.globl main
 
main: # $s0 = y, $s1 = z
    addi $s0, $zero, 0
    addi $s1, $zero, 0
    addi $sp, $sp, -4  # Aloca espaço na pilha
    sw   $ra, 0($sp)   # Salva $ra na pilha
    
    # Primeira chamada: y = func1(2, 3)
    addi $a0, $zero, 2
    addi $a1, $zero, 3
    jal func1
    add  $s0, $zero, $v0  # Armazena o retorno em y
    
    # Segunda chamada: z = func1(3, 2)
    addi $a0, $zero, 3
    addi $a1, $zero, 2
    jal func1
    add  $s1, $zero, $v0  # Armazena o retorno em z
    
    # Restaura $ra e desaloca a pilha
    lw   $ra, 0($sp)
    addi $sp, $sp, 4
    addi $v0, $zero, 0
    jr   $ra  # Retorna para o sistema
    
# Função func1(a0, a1)
func1:
    addi $sp, $sp, -4  # Aloca espaço na pilha
    sw   $ra, 0($sp)   # Salva $ra na pilha

    slt  $t0, $a0, $a1  # $t0 = 1 se a0 < a1, senão 0
    bne  $t0, $zero, else  # Se a0 < a1, vá para "else"

    jal  func2  # Chama func2(a0, a1)
    lw   $ra, 0($sp)  # Restaura $ra
    addi $sp, $sp, 4  # Desaloca a pilha
    jr   $ra  # Retorna

else:
    add  $t1, $a0, $zero  # Temporariamente salva a0 em t1
    add  $a0, $a1, $zero  # Troca a0 <-> a1
    add  $a1, $t1, $zero
    jal  func2  # Chama func2(a1, a0)

    lw   $ra, 0($sp)  # Restaura $ra
    addi $sp, $sp, 4  # Desaloca a pilha
    jr   $ra  # Retorna
    
# Função func2(a0, a1) retorna a0 - a1
func2:
    sub  $v0, $a0, $a1  # v0 = a0 - a1
    jr   $ra  # Retorna
