#include "Simulator.hpp"
#include <iostream>
#include <cstdint>
#include <vector>



std::uint32_t Simulator::j(){
	pc = (j_operands[0]*4-INSTR_MEM_BASE) - 4;
	//std::cout << ": " << pc << std::endl;
	std::cout << "Jump Address (PC): " << j_operands[0]*4-INSTR_MEM_BASE << std::endl;
	return 1;
}


std::uint32_t Simulator::add(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A+B; 
	reg.write(r_operands[2],result);
	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<0) && (B<0) && (result >=0)) ){
		std::cout << "Signed Overflow Exception code" << std:: endl;
	}
	//debugging
	//std:: cout << "Performing Add " <<std:: endl;
	//std::cout <<"R" << r_operands[2] << " = R" << r_operands[0] << " + R" << r_operands[1] << " = " <<std :: endl;
	std::cout << reg.read(r_operands[2]) << std::endl;

	return 1;
}