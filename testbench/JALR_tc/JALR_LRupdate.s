.set noreorder
.set noat
li $2, 0x0
jalr $31 , $2
add $2, $0, $31
nop
jalr $31 ,$2
nop
li $2, 0x5
nop
nop
nop
add $2, $0, $31
jalr $0
