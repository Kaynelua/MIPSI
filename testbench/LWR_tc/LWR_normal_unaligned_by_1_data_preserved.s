.set noreorder
.set noat
addi $1,$0,2061
li 	 $1,0x10000000
li   $2,0x12345678
lwr  $2,1($1)
srl  $2,$2,16
jr   $0
