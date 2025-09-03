.text
	.globl main
main: # Função Principal
	addi $a0, $0, 2		# f = 2
	addi $a1, $0, 3		# g = 3
	addi $a2, $0, 4		# h = 4
	addi $a3, $0, 5		# i = 5
	jal diffofsums # Chama a função		
				
						

diffofsums: # Função chamada com argumentos e faz tal cálculo (f+g)-(h+i)
	addi $sp, $sp, -4	# Aloca espaço na pilha para 3 registradores
	sw $s0, $sp(8)		# salva $s0 na pilha
	
	add $t0, $a0, $a1	# $t0 = (f+g)
	add $t1, $a2, $a3	# $t1 = (h+i)
	sub $t0, $t0, $t1	# $t0 = (f+g)-(h+i) 
	add $v0, $t0, $0	# $v0 = $t0
	
	lw $s0, 8($sp)		# restaura $s0 da pilha
	addi $sp, $sp, 4	# desaloca espaço na pilha
	jr $ra
