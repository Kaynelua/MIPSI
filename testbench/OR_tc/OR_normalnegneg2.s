.set noreorder
.set noat
li $3, 0x80000010
li $2, 0x80000001
or $2, $3, $2
jr   $0
