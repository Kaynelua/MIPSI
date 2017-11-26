.set noreorder
.set noat
li $2,0xF8123456
li $3,0x00000039
srav $2,$2,$3
jr   $0
