.set noreorder
.set noat
addi $1,$0,10
li 	 $1,0x10000002
lhu   $2,0($1)
jr   $0
