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
	std::uint32_t curr_inst = 0b00000000001000110001100000100000;//0x8000003;

	reg.write(1,-2147483648);
	reg.write(3,-1);



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
		/*for(int i=0; i<5;i++){
			std::cout << r_operands[i] << std::endl;
		}*/
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

std::uint32_t Simulator ::add(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A+B; 
	reg.write(r_operands[2],result);
	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<=0) && (B<=0) && (result >=0)) ){
		std::cout << "Signed Overflow Exception code" << std:: endl;
	}
	//debugging
	//std:: cout << "Performing Add " <<std:: endl;
	//std::cout <<"R" << r_operands[2] << " = R" << r_operands[0] << " + R" << r_operands[1] << " = " <<std :: endl;
	std::cout << reg.read(r_operands[2]) << std::endl;
}





