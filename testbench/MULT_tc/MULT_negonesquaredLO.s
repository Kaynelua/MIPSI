.set noreorder
.set noat
li $1, 0xFFFFFFFF
li $2, 0xFFFFFFFF
mult $1, $2
mflo $2 
jr   $0
