.set noreorder
.set noat
li 	 $3,0x20000042
sh   $3,-10($3)
lh   $2,-10($3)
jr   $0
