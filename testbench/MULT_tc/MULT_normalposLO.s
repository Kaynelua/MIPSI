.set noreorder
.set noat
li $1, 0x7FFFFFFF
li $2, 0x25
mult $1, $2
mflo $2 
jr   $0
