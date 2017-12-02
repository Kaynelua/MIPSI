.set noreorder
.set noat
li 	 $3,0x20000044
sw   $3,-8($3)
lw   $2,-8($3)
jr   $0
