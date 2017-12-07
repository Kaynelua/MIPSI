.set noreorder
.set noat
li $1, 0xFFFFFFCB
li $2, 0x55
multu $1, $2
mflo $2 
jr   $0
