.set noreorder
.set noat
li $1,0x51234567
li $3,0x0000003C
srav $2,$1,$3
jr   $0
