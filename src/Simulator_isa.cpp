#include "Simulator.hpp"
#include "Debug.hpp"
#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>


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
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump (PC):" << j_operands[0]*4 << std::endl;
	return 1;
}


/**************** R TYPE ******************/

std::uint32_t Simulator :: sll(){
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt << shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Shift left Logical by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: srl(){
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Shift right Logical by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: sra(){ 
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = (int32_t)rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Shift right Arithmetic by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: sllv(){
	uint32_t shiftamt = reg.read(r_operands[0]);
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt << shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Shift left Logical Variable by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: srlv(){
	uint32_t shiftamt = reg.read(r_operands[0]);
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Shift right Logical Variable by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: srav(){
	uint32_t shiftamt = reg.read(r_operands[0]);
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = (int32_t)rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Shift right Arithmetic Variable by " << shiftamt << std::endl;
}

std::uint32_t Simulator::jr(){
	uint32_t jd = reg.read(r_operands[0]);
	branch_address = jd;

	if(branch_address%4 == 0){
		branch_taken = 1;
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump Register (PC) -> " << jd << std::endl;
	}
	else{
		exit(-12);
	}
}

std::uint32_t Simulator::jalr(){ // KIV NOT SURE
	uint32_t jd = reg.read(r_operands[0]);
	uint32_t return_address = pc +8;
	reg.write(31,return_address);	
	branch_address = jd;
	
	// NEED TO MAKE ANOTHER EXCEPTION HERE WHEN RETURN ADDR = JUMP DESTINATION DUE TO RE-EXECUTION

	if(branch_address%4 == 0){
		branch_taken = 1;
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump Register (PC) -> " << jd << std::endl;
		debug << std::setw(21)  << std::left <<"RETURN ADDR IN R31" << return_address << std::endl;
	}
	else{
		exit(-12);
	}
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

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "ADDI :" << "R" << i_operands[1] << "= R"<<i_operands[0] << " + " <<  i_operands[2]<< std::endl;
	std::cout << reg.read(i_operands[1]) <<std::endl;
	return 1;
}

std::uint32_t Simulator::addiu(){
	//source : rs,imm
	//dest : rt
	int32_t A = reg.read(i_operands[0]);
	int32_t B = sign_extend(i_operands[2],16);
	int32_t result = A+B;
	reg.write(i_operands[1],result);

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "ADDIU :" << "R" << i_operands[1] << "= R"<<r_operands[0] << " + " << B << std::endl;
	return 1;

}









