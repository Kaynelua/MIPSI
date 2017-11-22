
testcases/PUTCCODE.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <.text>:
10000000:	20010003 	addi	at,zero,3
10000004:	00010f00 	sll	at,at,0x1c
10000008:	20020041 	addi	v0,zero,65
1000000c:	2003000a 	addi	v1,zero,10
10000010:	ac220004 	sw	v0,4(at)
10000014:	ac230004 	sw	v1,4(at)
10000018:	00000008 	jr	zero
1000001c:	00000000 	nop
