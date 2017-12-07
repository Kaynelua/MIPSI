.set noreorder
.set noat
li $1, 0xFABCDEFF
li $2, 0x0
mult $1, $2
mfhi $2 
jr   $0
