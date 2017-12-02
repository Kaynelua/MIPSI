.set noreorder
.set noat
li 	 $25,0x23FFFFFC
sw   $25,0($25)
lw   $2,0($25)
jr   $0
