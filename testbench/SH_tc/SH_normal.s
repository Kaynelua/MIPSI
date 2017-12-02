.set noreorder
.set noat
li 	 $3,0x20000012
sh   $3,0($3)
lh   $2,0($3)
jr   $0
