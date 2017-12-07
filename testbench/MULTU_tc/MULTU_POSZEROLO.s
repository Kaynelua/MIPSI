.set noreorder
.set noat
li $1, 0x0
li $2, 0x1ABCDEFF
multu $1, $2
mflo $2 
jr   $0
