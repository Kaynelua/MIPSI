
testbench/f.mips.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <entry>:
   0:	03e00008 	jr	ra
   4:	24020019 	li	v0,25

00000008 <getc>:
   8:	3c023000 	lui	v0,0x3000
   c:	8c420000 	lw	v0,0(v0)
  10:	03e00008 	jr	ra
  14:	00000000 	nop

00000018 <putc>:
  18:	3c023000 	lui	v0,0x3000
  1c:	ac440004 	sw	a0,4(v0)
  20:	03e00008 	jr	ra
  24:	00000000 	nop
	...
