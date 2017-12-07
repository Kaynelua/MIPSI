.set noreorder
li $3, 0x0
li $2, 0x1ABCDEFF
div $3, $2
mflo $2 
jr   $0
