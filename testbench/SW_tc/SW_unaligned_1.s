.set noreorder
.set noat
li 	 $3,0x20000016
sw   $3,0($3)
lw   $2,0($3)
jr   $0
