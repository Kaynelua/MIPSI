.set noreorder
.set noat
li   $3,0x80000002
sltiu $2, $3,0x7FFE
jr   $0
