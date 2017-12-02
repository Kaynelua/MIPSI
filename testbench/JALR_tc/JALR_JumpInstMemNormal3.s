.set noreorder
.set noat
li $2, 0x10000014
nop
jalr $26 ,$2
nop
li $2, 0x5
nop
nop
nop
jalr $0
