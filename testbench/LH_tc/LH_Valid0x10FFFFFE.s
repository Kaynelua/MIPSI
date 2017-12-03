.set noreorder
.set noat
li 	 $23,0x10FFFFFE
li   $2, 128
lh   $2,0($23)
jr   $0
