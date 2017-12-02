.set noreorder
.set noat
li 	 $23,0x10FFFFFF
li   $2, 128
LBU   $30,0($23)
jr   $0
