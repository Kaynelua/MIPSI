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



Simulator::Simulator(): pc(PC_INITIAL+4){
}

void Simulator::load_bin(const std::vector<std::uint8_t>& v_byte_inst){
	for(int i =0 ; i < v_byte_inst.size() ; i++){
		mem.write_inst((INSTR_MEM_BASE+4+i),v_byte_inst[i]);
	}
}

void Simulator::fetch_instruction(){
	instruction = mem.read_inst(pc);
}

std::uint32_t Simulator::run(){
	while(pc != ADDR_NULL){	//PC = 0 Signals completion of binary
		fetch_instruction();
		decode();
		pc = pc + 4;
	}

	return reg.read(2) & 0x000000FF; //MASK lower 8 bits of $2
}

void Simulator::decode(){

	std::uint32_t curr_inst = instruction;
	std::uint32_t opcode = ((curr_inst & OP_MASK) >> 26);
	std::uint32_t LHOP = (opcode & 0b111000) >> 3; 
	std::uint32_t RHOP =  (opcode & 0b000111);
	std::uint32_t LHFUNCT = (curr_inst & 0X00000038 )>>3;
	std::uint32_t RHFUNCT = curr_inst & 0X00000007;

	if(opcode == 0 ){ 	//R- TYPE
		//std:: cout << "R-type" << std::endl; 
		r_operands[0] = (curr_inst & RS_MASK) >> 21;
		r_operands[1] = (curr_inst & RT_MASK) >> 16;
		r_operands[2] = (curr_inst & RD_MASK) >> 11;
		r_operands[3] = (curr_inst & SHAMT_MASK) >> 6;
		r_operands[4] = (curr_inst & FUNCT_MASK);
		(this->*funct_table[LHFUNCT][RHFUNCT])();
	}
	else if( opcode == 2 || opcode ==3 ){	//J-TYPE
	 	//std:: cout << "J-type" << std:: endl; 
	 	j_operands[0] = (curr_inst & JA_MASK);
	 	
	 	(this->*opcode_table[LHOP][RHOP])();
	}
	else{	//I-TYPE
		//std:: cout << "I-type" << std :: endl; 
		i_operands[0] = (curr_inst & RS_MASK) >> 21;
		i_operands[1] = (curr_inst & RT_MASK) >> 16;
		i_operands[2] = (curr_inst & IM_MASK);	
		(this->*opcode_table[LHOP][RHOP])();
	}
}





