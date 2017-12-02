.set noreorder
.set noat
li $2, 0x1000001C
jalr $29 , $2
add $2, $0, $29
nop
jalr $29 ,$2
nop
li $2, 0x5
nop
nop
nop
add $2, $0, $29
jalr $0
