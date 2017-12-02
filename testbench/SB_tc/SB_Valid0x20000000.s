.set noreorder
.set noat
li 	 $24,0x20000000
sb   $24,0($24)
lb   $2,0($24)
jr   $0
