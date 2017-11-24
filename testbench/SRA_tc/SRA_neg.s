.set noreorder
.set noat
addi $2,$0,0xF812
sll  $2,$2,16
addi $2,$2,0x3456
sra  $2,$2,26
jr   $0
