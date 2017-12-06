.set noreorder
.set noat
li $2, 0x81234567
bltzal $2 , branchoffset00000008
li $31, 0xA0
branchoffset00000004 :
nop
branchoffset00000008 :
add $2, $0, $31
branchoffset0000000C :
nop
jr   $0
nop
