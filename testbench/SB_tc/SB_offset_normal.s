.set noreorder
.set noat
li 	 $2,0x20000007
sb   $2,5($2)
lb   $2,5($2)
jr   $0
