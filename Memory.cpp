#include "Memory.hpp"
#include "Debug.hpp"
#include <vector>
#include <iostream>



Memory::Memory() : INSTR_MEM(INSTR_MEM_LEN), DATA_MEM(DATA_MEM_LEN) {
}


std::uint32_t Memory::word_read(uint32_t R_ADDR, const std::vector<uint8_t>& v){
	return (v[R_ADDR]<<24) + (v[R_ADDR+1] <<16) +  (v[R_ADDR+2]<<8) + v[R_ADDR+3];
}


std::uint32_t Memory::read(int ADDR, bool mode){
	if(ADDR = ADDR_GETC){

	}
	else if(mode == WORD_RW){
		if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
			//std::cout << "READING FROM INSTRUCTION MEMORY" << std::endl;
			return word_read(ADDR-INSTR_MEM_BASE,INSTR_MEM);
		}
		else if(ADDR >= DATA_MEM_BASE && ADDR < DATA_MEM_BASE + DATA_MEM_LEN){
			//std::cout << "READING FROM DATA MEMORY" << std::endl;
			return word_read(ADDR-DATA_MEM_BASE,DATA_MEM);
		}
	}
	else if(mode == BYTE_RW){

	}
	return 0;	
}

std::uint32_t Memory::write(int ADDR, int DATA, bool mode){

	if(ADDR == ADDR_PUTC){

	}	
	else if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		//std::cout << "ERROR : CANNOT WRITE TO INSTRUCTION MEMORY" << std::endl;
	}
	else if(ADDR >= DATA_MEM_BASE && ADDR < DATA_MEM_BASE + DATA_MEM_LEN){
		//std::cout << "writing to data memoy" << std::endl;
	}	
	return 1;
}

std::uint32_t Memory::write_inst(uint32_t ADDR, uint8_t DATA){


	if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		//std::cout << "LOADING INTO INSTRUCITON MEMORY"<< std::endl;
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
		//debug << "READING FROM INSTRUCTION MEMORY" << std::endl;
		return word_read(R_ADDR,INSTR_MEM);
	}
	else{
		//debug << "CANNOT EXECUTE INSTRUCTION OUTSIDE OF INTSTRUCTION MEMORY" << std::endl;
		exit(-11);
	}

}
