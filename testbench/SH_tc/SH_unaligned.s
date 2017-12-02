.set noreorder
.set noat
li 	 $3,0x20000011
sh   $3,4($3)
lh   $2,4($3)
jr   $0
