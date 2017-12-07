.set noreorder
li $3, 0x1ABCDEFF
li $2, 0x0
divu $3, $2
mfhi $2 
jr   $0
