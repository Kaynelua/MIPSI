.set noreorder
.set noat
li $1, 0x7FFFFFFF
li $2, 0x25
multu $1, $2
mfhi $2 
jr   $0
