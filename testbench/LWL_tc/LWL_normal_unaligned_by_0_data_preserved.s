.set noreorder
.set noat
addi $1,$0,49127
li 	 $1,0x10000000
li   $2,0x12345678
lwl  $2,0($1)
jr   $0
