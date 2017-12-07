.set noreorder
.set noat
li $1, 0x81234565
li $3, 0x81234565
beq $1 , $3 , branchoffset00000018
li $2 , 0x47
branchoffset00000004 :
nop
branchoffset00000008 :
li $2, 0x35
branchoffset0000000C :
nop
jr   $0
nop
branchoffset00000018 : 
li $2, 0x80000043
beq $1 , $3 , branchoffset0000000C
branchoffset00000020 : 
nop
branchoffset00000024 : 
li $2 , 0x57
jr   $0
