.set noreorder
.set noat
li 	 $25,0x23FFFFFE
li   $2, 128
lh   $2,0($25)
jr   $0
