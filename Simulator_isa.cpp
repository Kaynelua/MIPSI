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


/**************** J TYPE ******************/
std::uint32_t Simulator::j(){
	pc = (j_operands[0]*4-INSTR_MEM_BASE) - 4;
	//std::cout << ": " << pc << std::endl;
	std::cout << "Jump Address (PC): " << j_operands[0]*4-INSTR_MEM_BASE << std::endl;
	return 1;
}


/**************** R TYPE ******************/

std::uint32_t Simulator::add(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A+B; 
	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<0) && (B<0) && (result >=0)) ){
		std::cout << "Signed Overflow Exception code" << std:: endl;
	}
	reg.write(r_operands[2],result);

	std::cout << reg.read(r_operands[2]) << std::endl;

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