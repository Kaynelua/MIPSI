.set noreorder
.set noat
li $2, 0x00000000
blez $2 , branchoffset0000000C
li $2, 0x47
branchoffset00000004 :
nop
branchoffset00000008 :
li $2, 0x35
branchoffset0000000C :
nop
jr   $0
li $2, 167 
