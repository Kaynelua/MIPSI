.set noreorder
.set noat
li 	 $24,0x20000000
sh   $24,0($24)
lh   $2,0($24)
jr   $0
