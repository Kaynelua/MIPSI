
testcases/SRAV_POS_RSNEG.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <.text>:
10000000:	20020001 	addi	v0,zero,1
10000004:	00021780 	sll	v0,v0,0x1e
10000008:	2001ffda 	addi	at,zero,-38
1000000c:	00221007 	srav	v0,v0,at
10000010:	00000008 	jr	zero
10000014:	00000000 	nop
	...
