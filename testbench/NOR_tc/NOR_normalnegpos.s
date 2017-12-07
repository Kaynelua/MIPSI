.set noreorder
.set noat
li $3, 0x80000030
li $2, 0x25
nor $2, $3, $2
jr   $0
