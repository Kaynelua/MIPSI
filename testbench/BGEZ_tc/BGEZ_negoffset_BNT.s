.set noreorder
.set noat
li $2, 0x20000000
bgez $2 , branchoffset00000018
li $2, 0x47
branchoffset00000004 :
nop
branchoffset00000008 :
li $2, 0x35
branchoffset0000000C :
nop
jr   $0
nop
branchoffset00000018 : 
li $2, 0x80000048
branchoffset0000001C : 
bgez $2 , branchoffset0000000C
branchoffset00000020 : 
nop
branchoffset00000024 : 
li $2, 0x57
jr   $0
