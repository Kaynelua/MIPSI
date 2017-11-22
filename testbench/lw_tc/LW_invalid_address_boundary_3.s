.set noreorder
.set noat
addi $1,$0,245
addi $3,$0,0x1100
sll  $3,$3,16
addi $3,$3,0x0000
lw   $2,0($3)
jr   $0
