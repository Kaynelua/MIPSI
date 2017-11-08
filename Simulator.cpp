/*
 * Simulator.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: kayne
 */

#include "Simulator.hpp"
#include <iostream>
#include <cstdint>
#include <vector>



Simulator::Simulator(): pc(4){
}


void Simulator::fetch_instruction(){
	instruction = mem.read_inst(INSTR_MEM_BASE+pc);
}


std::uint32_t Simulator::run(){
	while(pc != 0){	//sucessful exit is when pc == 0;
		fetch_instruction();
		decode();
		pc = pc + 4;
	}
	return reg.read(2) & 0x000000FF; //lower 8 bits of $2
}


Simulator::Simulator(std::uint32_t pc_in){
	pc = pc_in;
}


std::uint32_t Simulator::stub(){
	std::cout << "stub" << std::endl;
	return 1;
}



void Simulator::decode(){

	int curr_inst = instruction;
	
	int opcode = ((curr_inst & OP_MASK) >> 26);

	if(opcode == 0 ){ 	//R- TYPE
		//std:: cout << "R-type" << std::endl; 
		r_operands[0] = (curr_inst & RS_MASK) >> 21;
		r_operands[1] = (curr_inst & RT_MASK) >> 16;
		r_operands[2] = (curr_inst & RD_MASK) >> 11;
		r_operands[3] = (curr_inst & SHAMT_MASK) >> 6;
		r_operands[4] = (curr_inst & FUNCT_MASK);
		int LHFUNCT = (curr_inst & 0X00000038 )>>3;
		int RHFUNCT = curr_inst & 0X00000007;
		(this->*funct_table[LHFUNCT][RHFUNCT])();
	}
	else if( opcode == 2 || opcode ==3 ){	//J-TYPE
	 	//std:: cout << "J-type" << std:: endl; 
	 	j_operands[0] = (curr_inst & JA_MASK);
	 	int LHOP = (opcode & 0b111000) >> 3; 
	 	int RHOP =  (opcode & 0b000111);
	 	(this->*opcode_table[LHOP][RHOP])();
	}
	else{	//I-TYPE
		//std:: cout << "I-type" << std :: endl; 
		i_operands[0] = (curr_inst & RS_MASK) >> 21;
		i_operands[1] = (curr_inst & RT_MASK) >> 16;
		i_operands[2] = (curr_inst & IM_MASK);	
		int LHOP = (opcode & 0b111000) >> 3; 
	 	int RHOP =  (opcode & 0b000111);
		(this->*opcode_table[LHOP][RHOP])();
	}
}


void Simulator::load_bin(const std::vector<std::uint8_t>& vInst){
	for(int i =0 ; i < vInst.size() ; i++){
		mem.write_inst((INSTR_MEM_BASE+4+i),vInst[i]);
	}
}


