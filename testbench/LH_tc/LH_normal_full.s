.set noreorder
.set noat
addi $1,$0,59814
li 	 $1,0x10000002
lh   $3,0($1)
srl  $2,$3,8
add  $2,$2,$3
jr   $0
