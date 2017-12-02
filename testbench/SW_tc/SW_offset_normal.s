.set noreorder
.set noat
li 	 $3,0x20000008
sw   $3,16($3)
lw   $2,16($3)
jr   $0
