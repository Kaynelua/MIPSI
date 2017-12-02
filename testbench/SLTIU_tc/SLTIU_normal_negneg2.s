.set noreorder
.set noat
li   $3,0x80000001
sltiu $2, $3,0xFFFD
jr   $0
