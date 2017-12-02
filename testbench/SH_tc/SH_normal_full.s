.set noreorder
.set noat
li 	 $3,0x20000044
sh   $3,0($3)
lh   $2,0($3)
srl   $4,$2,8
addu  $2,$2,$4
jr   $0
