.set noreorder
.set noat
addi $1,$0,47777
li 	 $1,0x10000002
lhu   $2,0($1)
srl  $2,$2,9
jr   $0
