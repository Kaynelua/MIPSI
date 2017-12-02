.set noreorder
.set noat
li $2, 0x00000000
bgezal $2 , branchoffset0000000C
li $31 , 0x45
branchoffset00000004 :
nop
branchoffset00000008 :
li $2, 0x35
branchoffset0000000C :
nop
jr   $0
add $2, $0, $31
