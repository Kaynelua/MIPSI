.set noreorder
.set noat
addi $1,$0,4721
li 	 $1,0x10000000
lw   $2,0($1)
srl   $4,$2,8
addu  $2,$2,$4
srl   $4,$4,8
addu  $2,$2,$4
srl   $4,$4,8
addu  $2,$2,$4
jr   $0
