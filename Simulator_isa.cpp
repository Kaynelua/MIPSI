#include "Simulator.hpp"
#include <iostream>
#include <cstdint>
#include <vector>


/*************** HELPER FUCNTIONS ********/
std::uint32_t Simulator::sign_extend(std::int32_t a,int bits){
	a = a << (32-bits);
	a = a >> (32-bits);
	return a;
}

std::uint32_t Simulator::stub(){
	std::cout << "stub" << std::endl;
	return 1;
}

/**************** J TYPE ******************/
std::uint32_t Simulator::j(){
	branch_address = (j_operands[0]*4);
	branch_taken = 1;
	//std::cout << ": " << pc << std::endl;
	std::cout << "Jump Address (PC): " << j_operands[0]*4-INSTR_MEM_BASE << std::endl;
	return 1;
}


/**************** R TYPE ******************/

std::uint32_t Simulator::jr(){
	uint32_t ja = mem.read(r_operands[0]);
	branch_address = ja;
	branch_taken = 1;
	std::cout << "Jump Register (PC): " << j_operands[0]*4 << std::endl;
	return 1;
}

std::uint32_t Simulator::add(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A+B; 
	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<0) && (B<0) && (result >=0)) ){
		std::cout << "Signed Overflow Exception code" << std:: endl;
	}

	//debugging
	std:: cout << "Performing Add " <<std:: endl;
	std::cout <<"R" << r_operands[2] << " = R" << r_operands[0] << " + R" << r_operands[1] << " = " <<std :: endl;
	reg.write(r_operands[2],result);

	std::cout << reg.read(r_operands[2]) << std::endl;

	return 1;
}

std::uint32_t Simulator::addu(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A+B; 
	reg.write(r_operands[2],result);
	//debugging
	std:: cout << "Performing Addu " <<std:: endl;
	std::cout <<"R" << r_operands[2] << " = R" << r_operands[0] << " + R" << r_operands[1] << " = " <<std :: endl;
	std::cout << reg.read(r_operands[2]) << std::endl;

	return 1;
}

std::uint32_t Simulator::sub(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A-B; 
	reg.write(r_operands[2],result);
	if( ((A >= 0) && (B< 0) && (result < 0)) || ((A<0) && (B>=0) && (result >=0)) ){
		std::cout << "Signed Overflow Exception code" << std:: endl;
	}
	//debugging
	std:: cout << "Performing Sub " <<std:: endl;
	std::cout <<"R" << r_operands[2] << " = R" << r_operands[0] << " - R" << r_operands[1] << " = " <<std :: endl;
	std::cout << (int)reg.read(r_operands[2]) << std::endl;

	return 1;
}

/**************** I TYPE ******************/
std::uint32_t Simulator::addi(){
	//source : rs,imm
	//dest : rt
	int32_t A = reg.read(i_operands[0]);
	int32_t B = sign_extend(i_operands[2],16);
	int32_t result = A+B;
	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<0) && (B<0) && (result >=0)) ){
		std::cout << "Signed Overflow Exception code" << std:: endl;
	}
	reg.write(i_operands[1],result);


	return 1;
}

std::uint32_t Simulator::addiu(){
	//source : rs,imm
	//dest : rt
	int32_t A = reg.read(i_operands[0]);
	int32_t B = sign_extend(i_operands[2],16);
	int32_t result = A+B;
	reg.write(i_operands[1],result);
	return 1;

}









