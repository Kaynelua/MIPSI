.set noreorder
.set noat

addi $1,$0,3
sll  $1,$1,28
#addi $1,$1,4
addi $3,$0,10
lw	 $2,0($1)
sra  $2,$2,1	
sb	 $2,7($1)
sb	 $3,7($1)
jr $0