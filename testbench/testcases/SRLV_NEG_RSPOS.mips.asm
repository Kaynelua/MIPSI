
testcases/SRLV_NEG_RSPOS.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <.text>:
10000000:	2002ffff 	addi	v0,zero,-1
10000004:	2001001d 	addi	at,zero,29
10000008:	00221006 	srlv	v0,v0,at
1000000c:	00000008 	jr	zero
