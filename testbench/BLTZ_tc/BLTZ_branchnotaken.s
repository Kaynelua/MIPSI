.set noreorder
.set noat
li $2, 0x00000001
bltz $2 , branchoffset
nop
nop
li $2, 0x35
branchoffset : 
 nop
jr   $0
