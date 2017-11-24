.set noreorder
.set noat
addi $2,$0,0xFFFF
sll  $2,$2,16
addi $2,$2,0xFFFF
sra  $2,$2,0
jr   $0
