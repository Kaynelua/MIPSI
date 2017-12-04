
testbench/DIV_tc/DIV_NEGZEROLO.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <.text>:
10000000:	24030000 	li	v1,0
10000004:	3c02fabc 	lui	v0,0xfabc
10000008:	3442deff 	ori	v0,v0,0xdeff
1000000c:	14400002 	bnez	v0,0x10000018
10000010:	0062001a 	div	zero,v1,v0
10000014:	0007000d 	break	0x7
10000018:	2401ffff 	li	at,-1
1000001c:	14410004 	bne	v0,at,0x10000030
10000020:	3c018000 	lui	at,0x8000
10000024:	14610002 	bne	v1,at,0x10000030
10000028:	00000000 	nop
1000002c:	0006000d 	break	0x6
10000030:	00001812 	mflo	v1
10000034:	00001012 	mflo	v0
10000038:	00000008 	jr	zero
1000003c:	00000000 	nop

Disassembly of section .reginfo:

10000040 <.reginfo>:
10000040:	0000000e 	0xe
	...

Disassembly of section .MIPS.abiflags:

10000058 <.MIPS.abiflags>:
10000058:	00000100 	sll	zero,zero,0x4
1000005c:	01010001 	0x1010001
	...

Disassembly of section .gnu.attributes:

00000000 <.gnu.attributes>:
   0:	41000000 	bc0f	0x4
   4:	0f676e75 	jal	0xd9db9d4
   8:	00010000 	sll	zero,at,0x0
   c:	00070401 	0x70401
