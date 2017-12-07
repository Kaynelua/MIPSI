.set noreorder
.set noat
li $2, 0x00000000
bltzal $2 , branchoffset00000008
nop
branchoffset00000004 :
nop
branchoffset00000008 :
add $2, $0, $31
branchoffset0000000C :
nop
jr   $0
nop
