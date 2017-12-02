.set noreorder
li $3, 0x0
li $2, 0xFABCDEFF
div $3, $2
mflo $2 
jr   $0
