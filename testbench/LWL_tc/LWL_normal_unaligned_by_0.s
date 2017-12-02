.set noreorder
.set noat
addi $1,$0,2061
li 	 $1,0x10000000
lwl  $2,0($1)
srl  $2,$2,0
jr   $0
