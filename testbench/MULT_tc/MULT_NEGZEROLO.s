.set noreorder
.set noat
li $1, 0x0
li $2, 0xFABCDEFF
mult $1, $2
mflo $2 
jr   $0
