.set noreorder
.set noat
li $2, 0x10000020
nop
jalr $31 ,$2
nop
li $2, 0x5
nop
nop
nop
jalr $0
