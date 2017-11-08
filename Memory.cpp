#include "Memory.hpp"
#include <vector>
#include <iostream>



Memory::Memory() : INSTR_MEM(INSTR_MEM_LEN), DATA_MEM(DATA_MEM_LEN) {

}

int Memory::read(int ADDR, bool mode){

	//RESOLVE memory range here?
	return 1;
}

int Memory::write(int ADDR, int DATA, bool mode){

	//RESOLVE memory range here?	
	if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		std::cout << "ERROR : CANNOT WRITE TO INSTRUCTION MEMORY" << std::endl;
	}
	else if(ADDR >= DATA_MEM_BASE && ADDR < DATA_MEM_BASE + DATA_MEM_LEN){
		std::cout << "writing to data memoy" << std::endl;
	}	
	return 1;
}

int Memory::writeInst(int ADDR, int DATA){

	//RESOLVE memory range here?	
	if(ADDR >= INSTR_MEM_BASE && ADDR < INSTR_MEM_BASE + INSTR_MEM_LEN){
		std::cout << "Loading to Instruction Memory"<< std::endl;
	}
	else{
		std::cout << "Error Loading Binary Instructions" << std::endl;
	}	
	return 1;
}
