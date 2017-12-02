.set noreorder
.set noat
li $1, 0xFB287579
li $2, 0xC5838C79
mult $1, $2
mfhi $2 
jr   $0
