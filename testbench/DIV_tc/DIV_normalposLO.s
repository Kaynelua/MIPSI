.set noreorder
li $3, 0x7FFFFFFF
li $2, 0x25
div $3, $2
mflo $2 
jr   $0
