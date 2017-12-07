.set noreorder
.set noat
li 	 $25,0x23FFFFFF
li   $2, 128
LBU   $2,0($25)
jr   $0
