.set noreorder
.set noat
addi $1,$0,0x7123
sll  $1,$1,16
addi $1,$1,0x4567
sra  $2,$1,28
jr   $0
