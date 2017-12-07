.set noreorder
.set noat
li $1, 0xFFFFFFFF
li $2, 0xFFFFFFFF
multu $1, $2
mfhi $2 
jr   $0
