.set noreorder
.set noat
addi $1,$0,0x    
sll  $1,$1,16
addi $1,$1,0x    
srl  $2,$1,2
jr   $0
