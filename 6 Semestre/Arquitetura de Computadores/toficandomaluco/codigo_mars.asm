lw $t0, 0($zero)
lw $t1, 4($zero)

beq $t0, $t1, else
sub $t2, $t0, $t1
j exit

else:
add $t2, $t0, $t1

exit:
addi $t2, $t2, 10
sw $t2, 8($zero)