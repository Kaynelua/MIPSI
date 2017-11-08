#include "Memory.hpp"
#include <vector>
#include <iostream>



Memory::Memory() : INSTR_MEM(INSTR_MEM_LEN), DATA_MEM(DATA_MEM_LEN) {
}

int Memory::read(int ADDR, bool mode){
	if(mode == WORD_RW){
		if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
			//std::cout << "READING FROM INSTRUCTION MEMORY" << std::endl;
			return (INSTR_MEM[ADDR-INSTR_MEM_BASE]<<24) + (INSTR_MEM[ADDR-INSTR_MEM_BASE+1] <<16) +  (INSTR_MEM[ADDR-INSTR_MEM_BASE+2]<<8) + INSTR_MEM[ADDR-INSTR_MEM_BASE+3];
		}
		else if(ADDR >= DATA_MEM_BASE && ADDR < DATA_MEM_BASE + DATA_MEM_LEN){
			//std::cout << "READING FROM DATA MEMORY" << std::endl;
			return INSTR_MEM[ADDR-DATA_MEM_BASE];
		}
	}
	else if(mode == BYTE_RW){

	}
	return 0;	
}

int Memory::write(int ADDR, int DATA, bool mode){

	//RESOLVE memory range here?	
	if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		//std::cout << "ERROR : CANNOT WRITE TO INSTRUCTION MEMORY" << std::endl;
	}
	else if(ADDR >= DATA_MEM_BASE && ADDR < DATA_MEM_BASE + DATA_MEM_LEN){
		//std::cout << "writing to data memoy" << std::endl;
	}	
	return 1;
}

int Memory::write_inst(uint32_t ADDR, uint8_t DATA){

	//RESOLVE memory range here?	
	if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		//std::cout << "LOADING INTO INSTRUCITON MEMORY"<< std::endl;
		INSTR_MEM[ADDR-INSTR_MEM_BASE] = DATA;
	}
	else{
		//std::cout << "Error Loading Binary Instructions" << std::endl;
	}	
	return 1;
}
