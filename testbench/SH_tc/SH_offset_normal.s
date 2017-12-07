.set noreorder
.set noat
li 	 $3,0x20000040
sh   $3,22($3)
lh   $2,22($3)
jr   $0
