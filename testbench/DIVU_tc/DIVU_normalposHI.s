.set noreorder
li $3, 0x7FFFFFFF
li $2, 0x25
divu $3, $2
mfhi $2 
jr   $0
