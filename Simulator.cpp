/*
 * Simulator.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: kayne
 */

#include "Simulator.hpp"
#include <iostream>
#include <cstdint>



Simulator::Simulator(): pc(4){
}



Simulator::Simulator(std::uint32_t pc_in){
	pc = pc_in;
}


std::uint32_t Simulator::stub(){
	std::cout << "LOz" << std::endl;
	return 1;
}

std::uint32_t Simulator::j(){
	std::cout << "Jump Address : " <<j_operands[0] << std::endl;
	return 1;
}

void Simulator::run(){
	std::cout << "current pc val : " << pc << std::endl;
	decode();

}

void Simulator::decode(){

	//int curr_inst = mem.read(pc);
	std::uint32_t curr_inst =0x8000003;
	int opcode = ((curr_inst & OP_MASK) >> 26);

	if(opcode == 0 ){ 	//R- TYPE
		//std:: cout << "R-type" << std::endl; 
		r_operands[0] = (curr_inst & RS_MASK) >> 21;
		r_operands[1] = (curr_inst & RT_MASK) >> 16;
		r_operands[2] = (curr_inst & RD_MASK) >> 11;
		r_operands[3] = (curr_inst & SHAMT_MASK) >> 6;
		r_operands[4] = (curr_inst & FUNCT_MASK);
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
		(this->*opcode_table[4][4])();
	}
}







