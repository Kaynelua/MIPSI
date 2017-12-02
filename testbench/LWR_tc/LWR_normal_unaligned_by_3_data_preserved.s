.set noreorder
.set noat
addi $1,$0,2061
li 	 $1,0x10000000
li   $2,0x12345678
lwr  $2,3($1)
jr   $0
