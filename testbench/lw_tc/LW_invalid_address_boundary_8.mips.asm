
testbench/lw_tc/LW_invalid_address_boundary_8.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <.text>:
10000000:	200100f5 	addi	at,zero,245
10000004:	20034000 	addi	v1,zero,16384
10000008:	00031c00 	sll	v1,v1,0x10
1000000c:	20630008 	addi	v1,v1,8
10000010:	8c620000 	lw	v0,0(v1)
10000014:	00000008 	jr	zero
10000018:	00000000 	nop
1000001c:	00000000 	nop
