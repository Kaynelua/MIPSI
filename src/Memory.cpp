#include "Memory.hpp"
#include "Debug.hpp"
#include <vector>
#include <iostream>



Memory::Memory() : INSTR_MEM(INSTR_MEM_LEN), DATA_MEM(DATA_MEM_LEN) {
}


std::uint32_t Memory::word_read(uint32_t R_ADDR, const std::vector<uint8_t>& v){
	return (v[R_ADDR]<<24) + (v[R_ADDR+1] <<16) +  (v[R_ADDR+2]<<8) + v[R_ADDR+3];
}

std::uint32_t Memory::word_write(uint32_t R_ADDR, uint32_t DATA, std::vector<uint8_t>& v){
	//v[R_ADDR]<<24) + (v[R_ADDR+1] <<16) +  (v[R_ADDR+2]<<8) + v[R_ADDR+3];
	v[R_ADDR] =   (DATA & 0xFF000000 ) >> 24;
	v[R_ADDR+1] = (DATA & 0x00FF0000 ) >> 16;
	v[R_ADDR+2] = (DATA & 0x0000FF00 ) >> 8;
	v[R_ADDR+3] = (DATA & 0x0000000FF );
}

std::uint32_t Memory::half_word_read(uint32_t R_ADDR, const std::vector<uint8_t>& v){
	return (v[R_ADDR]<<8) + (v[R_ADDR+1]);
}

std::uint32_t Memory::half_word_write(uint32_t R_ADDR, uint32_t DATA, std::vector<uint8_t>& v){ //wrong for now
	v[R_ADDR  ] =   (DATA & 0x0000FF00 ) >> 8;
	v[R_ADDR+1] = (DATA & 0x000000FF );

}


std::uint32_t Memory::read(uint32_t ADDR, char mode){
	if(ADDR == ADDR_GETC && mode == WORD_RW){
		int32_t c;
		c = std::getchar();
		if(c==-1){
			return -1;
		}
		else{
			uint8_t ch = (uint8_t)c;
			return uint32_t(ch);
		}	
	}
	else if(ADDR == ADDR_GETC_HW && mode == HWORD_RW){
		int32_t c;
		c = std::getchar();
		if(c==-1){
			return -1;
		}
		else{
			uint8_t ch = (uint8_t)c;
			return uint32_t(ch);
		}
	}
	else if(ADDR == ADDR_GETC_B && mode == BYTE_RW){
		int32_t c;
		c = std::getchar();
		if(c==-1){
			return -1;
		}
		else{
			uint8_t ch = (uint8_t)c;
			return uint32_t(ch);
		}
	}
	else if(ADDR >= DATA_MEM_BASE && ADDR < DATA_MEM_BASE + DATA_MEM_LEN){ // READING FROM DATA MEMORY
		if(mode == WORD_RW){
			return word_read(ADDR-DATA_MEM_BASE,DATA_MEM);
		}
		else if(mode == HWORD_RW){
			return half_word_read(ADDR-DATA_MEM_BASE,DATA_MEM);
		}
		else if(mode == BYTE_RW){
			return DATA_MEM[ADDR-DATA_MEM_BASE];
		}
	}
	else if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){	//READING FROM INSTRUCTION MEMORY
		if(mode == WORD_RW){
			return word_read(ADDR-INSTR_MEM_BASE,INSTR_MEM);
		}
		else if(mode == HWORD_RW){
			return half_word_read(ADDR-INSTR_MEM_BASE,INSTR_MEM);
		}
		else if(mode == BYTE_RW){
			return INSTR_MEM[ADDR-INSTR_MEM_BASE];
		}
	}
	else{
		exit(-11);
	}
	return 0;	
}

std::uint32_t Memory::write(uint32_t ADDR, uint32_t DATA, char mode){
	if(ADDR == ADDR_PUTC && mode == WORD_RW){
		uint8_t c = (DATA & 0XFF);
		std::putchar(c);
	}
	else if(ADDR == ADDR_PUTC_HW && mode == HWORD_RW){
		uint8_t c = (DATA & 0XFF);
		std::putchar(c);

	}
	else if(ADDR == ADDR_PUTC_B && mode == BYTE_RW){
		uint8_t c = (DATA & 0XFF);
		std::putchar(c);
	}
	else if(ADDR >= DATA_MEM_BASE && ADDR < DATA_MEM_BASE + DATA_MEM_LEN){ // WRITING TO DATA MEMORY
		if(mode == WORD_RW){
			word_write(ADDR-DATA_MEM_BASE,DATA,DATA_MEM);
		}
		else if(mode == HWORD_RW){
			half_word_write(ADDR-DATA_MEM_BASE,DATA,DATA_MEM);
		}
		else if(mode == BYTE_RW){
			DATA_MEM[ADDR-DATA_MEM_BASE] = DATA;	// NEED TO MASK??? 	
		}
	}
	else{
		exit(-11);
	}

	return 1;
}

std::uint32_t Memory::write_inst(uint32_t ADDR, uint8_t DATA){
	if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		INSTR_MEM[ADDR-INSTR_MEM_BASE] = DATA;
	}
	else{
		//std::cout << "Error Loading Binary Instructions" << std::endl;
	}	
	return 1;
}

std::uint32_t Memory::read_inst(uint32_t ADDR){
	uint32_t R_ADDR = ADDR-INSTR_MEM_BASE;
	if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		return word_read(R_ADDR,INSTR_MEM);
	}
	else{	//EXECUTING OUTSIDE INSTRUCTION MEMORY
		debug  << "INVALID INSTR" << std::endl;
		exit(INVALID_INSTRUCTION);
	}

}
