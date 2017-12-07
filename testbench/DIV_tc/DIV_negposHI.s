.set noreorder
li $3, 0x80000000
li $2, 0x55
div $3, $2
mfhi $2 
jr   $0
