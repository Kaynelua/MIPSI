.set noreorder
.set noat
li $2, 0x10000018
nop
jalr $28 ,$2
nop
li $2, 0x5
nop
nop
nop
jalr $0
