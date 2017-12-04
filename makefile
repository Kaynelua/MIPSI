###################################################
## MIPS Compilation path

MIPS_CC = mips-linux-gnu-gcc
MIPS_OBJCOPY = mips-linux-gnu-objcopy
MIPS_OBJDUMP = mips-linux-gnu-objdump

# Turn on all warnings, and enable optimisations
MIPS_CPPFLAGS = -W -Wall -O0 -fno-builtin -mfp32 -mgp32 -march=mips1 -mno-check-zero-division 

# Avoid standard libraries etc. being brought in, and link statically
MIPS_LDFLAGS = -nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic
MIPS_LDFLAGS += -Wl,--build-id=none

# Compile a c file into a MIPS object file
%.mips.o : %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

%.mips.s : %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -S $< -o $@

# Compile a s file into a MIPS object file
%.mips.o : %.s
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

# Link a MIPS object file and place it at the locations required in the
# spec using linker.ld
%.mips.elf : %.mips.o
	$(MIPS_CC) $(MIPS_CPPFLAGS) $(MIPS_LDFLAGS) -T src/linker.ld $< -o $@

# Extract machine instructions from object file
%.mips.asm : %.mips.elf
	$(MIPS_OBJDUMP) -d $< > $@

# Extract just the binary instructions from the object file
%.mips.bin : %.mips.elf
	$(MIPS_OBJCOPY) -O binary --only-section=.text $< $@

# For example, if you have testbench/test.c, you can do:
#
# make testbench/test.mips.bin

###################################################
## Simulator

# Build the simulation binary
bin/mips_simulator : src/Simulator.cpp
	mkdir -p bin
	g++ -W -Wall src/*.cpp -std=c++11 -o bin/mips_simulator

# In order to comply with spec
simulator : bin/mips_simulator

###################################################
## Testbench
bin/mips_testbench : testbench/testbench.sh
	@mkdir -p bin
	@cp testbench/testbench.sh bin/mips_testbench
	@chmod +x bin/mips_testbench

testbench : bin/mips_testbench







