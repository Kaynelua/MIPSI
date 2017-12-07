.set noreorder
.set noat
li $3, 0x00000000
li $2, 0xAB123456
sltu $2, $3, $2
jr   $0
