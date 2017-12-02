.set noreorder
.set noat
li 	 $0,0x20000033
li   $2, 128
lh   $2,0($0)
jr   $0
