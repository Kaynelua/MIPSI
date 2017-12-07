.set noreorder
.set noat
li   $3,2611121327
li 	 $2,0x20000000
sw   $3,0($2)
lwr  $2,3($2)
srl  $2,$2,25
jr   $0
