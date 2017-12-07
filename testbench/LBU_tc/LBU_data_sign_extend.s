.set noreorder
.set noat
addi $1,$0,185
li 	 $1,0x10000003
LBU   $2,0($1)
srl  $2,$2,1
jr   $0
