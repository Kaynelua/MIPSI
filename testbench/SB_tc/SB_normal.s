.set noreorder
.set noat
li 	 $2,0x20000013
sb   $2,0($2)
lb   $2,0($2)
jr   $0
