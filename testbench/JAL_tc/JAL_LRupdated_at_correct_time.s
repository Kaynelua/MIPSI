.set noreorder
.set noat
.word 0x0C000003
li $31,0x5989
nop
add $2,$0,$31
jr   $0
