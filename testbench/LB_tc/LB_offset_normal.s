.set noreorder
.set noat
addi $1,$0,10
li 	 $1,0x10000003
lb   $2,0($1)
jr   $0
