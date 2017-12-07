.set noreorder
.set noat
li 	 $25,0x23FFFFFF
sb   $25,0($25)
lb   $2,0($25)
jr   $0
