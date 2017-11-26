.set noreorder
.set noat
li $2,0xFFFFFFFF
li $3,0x00000050
srav $2,$2,$3
jr   $0
