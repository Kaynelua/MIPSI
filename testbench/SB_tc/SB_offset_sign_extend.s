.set noreorder
.set noat
li 	 $2,0x20000045
sb   $2,-7($2)
lb   $2,-7($2)
jr   $0
