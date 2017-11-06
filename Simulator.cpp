/*
 * Simulator.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: kayne
 */

#include "Simulator.hpp"
#include <iostream>
#include <cstdint>

//int (Simulator::*opcode_function_table[8][8])() = {NULL};


Simulator::Simulator(): pc(4){

	for(int i= 0 ; i < 8 ; i++){
		for(int j=0; j <8 ; j++){
		opcode_function_table[i][j] = &Simulator::stub;
		}
	}

	opcode_function_table[4][0] = &Simulator::add;
	//opcode_function_table[4][1] = &Simulator::addu;
}


Simulator::Simulator(std::uint32_t pc_in){
	pc = pc_in;
}


std::uint32_t Simulator::stub(){
	std::cout << "LOL" << std::endl;
	return 1;
}

void Simulator::run(){
	std::cout << "current pc val : " << pc << std::endl;
	decode();

}

void Simulator::decode(){

	//int curr_inst = mem.read(pc);
	std::uint32_t curr_inst = 0b00000000011000110001100000100000;//1007157503;//36847648;//0x00000000; //hardcoded
	int opcode = ((curr_inst & OP_MASK) >> 26);

	if(opcode == 0 ){ 	//R- TYPE - OK
		//std:: cout << "R-type" << std::endl; 
		r_operands[0] = (curr_inst & RS_MASK) >> 21;
		r_operands[1] = (curr_inst & RT_MASK) >> 16;
		r_operands[2] = (curr_inst & RD_MASK) >> 11;
		r_operands[3] = (curr_inst & SHAMT_MASK) >> 6;
		r_operands[4] = (curr_inst & FUNCT_MASK);
		int LHFUNCT = (curr_inst & 0X00000038 )>>3;
		int RHFUNCT = curr_inst & 0X00000007;
		(this->*opcode_function_table[LHFUNCT][RHFUNCT])();
		/*for(int i=0; i<5;i++){
			std::cout << r_operands[i] << std::endl;
		}*/
	}
	else if( opcode == 2 || opcode ==3 ){
		(this->*opcode_function_table[5][0])();
	 	//std:: cout << "J-type" << std:: endl; 
	 	j_operands[0] = (curr_inst & JA_MASK);
	 	/*for(int i=0; i<1;i++){
			std::cout << j_operands[i] << std::endl;
		}*/
	}
	else{
		//std:: cout << "I-type" << std :: endl; 
		i_operands[0] = (curr_inst & RS_MASK) >> 21;
		i_operands[1] = (curr_inst & RT_MASK) >> 16;
		i_operands[2] = (curr_inst & IM_MASK);	
		/*for(int i=0; i<3;i++){
			std::cout << i_operands[i] << std::endl;
		}*/
	}
}

std::uint32_t Simulator ::add(){
	std:: cout << "Performing Add " <<std:: endl;
	std::cout <<"R" << r_operands[2] << " = R" << r_operands[0] << " + R" << r_operands[1] << " = " <<std :: endl;
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = A+B; 
	reg.write(reg.read(r_operands[2]),result);
	std::cout << reg.read(r_operands[2]) << std::endl;

	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<=0) && (B<=0) && (result >=0)) ){
		std::cout << "Signed Overflow Exception code" << std:: endl;
	}
}





