.set noreorder
li $3, 0x80000000
li $2, 0x55
divu $3, $2
mflo $2 
jr   $0
