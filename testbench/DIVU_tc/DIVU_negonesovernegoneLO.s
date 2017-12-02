.set noreorder
li $3, 0xFFFFFFFF
li $2, 0xFFFFFFFF
divu $3, $2
mflo $2 
jr   $0
