.set noreorder
.set noat
li 	 $25,0x23FFFFFE
sh   $25,0($25)
lh   $2,0($25)
jr   $0
