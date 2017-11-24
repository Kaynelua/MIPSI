.set noreorder
.set noat
addi $2,$0,0x0000
sll  $2,$2,16
addi $2,$2,0x0000
sra  $2,$2,1
jr   $0
