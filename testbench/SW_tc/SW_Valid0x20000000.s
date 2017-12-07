.set noreorder
.set noat
li 	 $24,0x20000000
sw   $24,0($24)
lw   $2,0($24)
jr   $0
