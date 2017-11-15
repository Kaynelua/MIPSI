#include "Simulator.hpp"
#include "Memory.hpp"
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
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump (PC):" << j_operands[0]*4 << std::endl;
	return 1;
}

std::uint32_t Simulator::jal(){
	branch_address = (j_operands[0]*4);
	branch_taken = 1;
	uint32_t return_address = pc +8;
	reg.write(31,return_address);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump and Link (PC): Branch Target=" << branch_address << std::endl;
	debug <<"RETURN ADDR IN R31 = " << return_address << std::endl;
	return 1;
}


/**************** R TYPE ******************/

std::uint32_t Simulator :: sll(){
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt << shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] <<" = R" << r_operands[1] << " Shift left Logical by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: srl(){
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] <<" = R" << r_operands[1] << " Shift Right Logical by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: sra(){ 
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = (int32_t)rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] <<" = R" << r_operands[1] << " Shift Right Arithmetic by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: sllv(){
	uint32_t shiftamt = reg.read(r_operands[0]);
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt << shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] << " = R" <<r_operands[1] << " Shift left Logical Variable by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: srlv(){
	uint32_t shiftamt = reg.read(r_operands[0]);
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] << " = R" <<r_operands[1] << " Shift Right Logical Variable by " << shiftamt << std::endl;
}

std::uint32_t Simulator :: srav(){
	uint32_t shiftamt = reg.read(r_operands[0]);
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = (int32_t)rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] << " = R" <<r_operands[1] << " Shift Right Arithmetic Variable by " << shiftamt << std::endl;
}

std::uint32_t Simulator::jr(){	// JUMPING to invalid PC INSTRUCTION ADDRESS
	uint32_t jd = reg.read(r_operands[0]);
	
	if(jd%4 == 0){
		branch_address = jd;
		branch_taken = 1;
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump Register (PC) -> " << jd << std::endl;
	}
	else{
		exit(-12);
	}
}

std::uint32_t Simulator::jalr(){ // KIV NOT SURE about this when RS == R31 (LR ) Undefined behaviour
	uint32_t jd = reg.read(r_operands[0]);
	uint32_t return_address = pc +8;
	reg.write(31,return_address);	// SHOULD RETURN ADDRESS BE WRITTEN HERE ? DOES IT DEPENDS ON whether address is valid before they write to R31?
		

	if(branch_address%4 == 0){
		branch_address = jd;
		branch_taken = 1;
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump Register (PC) -> " << jd << std::endl;
		debug <<"RETURN ADDR IN R31 = " << return_address << std::endl;
	}
	else{
		exit(-12);
	}
}

std::uint32_t Simulator::mfhi(){	// UNHANDLED: Reads of HI/LO Register must be separated from any instructions that writes to them by 2 or more
	
	int32_t data =  reg.regHI;
	reg.write(r_operands[2],data);
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move From HI " << std::endl;
	debug << "R" << r_operands[2] << " = " << reg.read(r_operands[2])  << std::endl;

	return 1;
}

std::uint32_t Simulator::mthi(){
	
	int32_t data =  reg.read(r_operands[0]);
	reg.regHI = data;
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move TO HI " << std::endl;
	debug << "reg HI = R"  << r_operands[0] << " = " << data << std::endl;

	return 1;
}

std::uint32_t Simulator::mflo(){
	
	int32_t data =  reg.regLO;
	reg.write(r_operands[2],data);
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move From LO " << std::endl;
	debug << "R" << r_operands[2] << " = " << reg.read(r_operands[2])  << std::endl;

	return 1;
}

std::uint32_t Simulator::mtlo(){
	
	int32_t data =  reg.read(r_operands[0]);
	reg.regLO = data;
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move TO LO " << std::endl;
	debug << "reg LO = R"  << r_operands[0] << " = " << data << std::endl;

	return 1;
}

std::uint32_t Simulator::mult(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int64_t result = (int64_t)A * (int64_t)B; 
	uint64_t UHresult =((uint64_t) (result & 0xFFFFFFFF00000000) ) >> 32;
	uint32_t LHresult = (uint32_t)(result & 0xFFFFFFFF);
	reg.regHI = uint32_t(UHresult);
	reg.regLO = LHresult;
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Multiply " << std::endl;
	debug <<  "R" << r_operands[0] << " * R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "HI = " << reg.regHI << " LO = " << reg.regLO << std::endl;

	return 1;
}

std::uint32_t Simulator::multu(){	// NOT QUITE SURE WHAT UNSIGNED MULTIPLY MEANS /DIFFER OTHER THAN OPERANDS BEING UNSIGNED
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint64_t result = (uint64_t)A * (uint64_t)B; 
	uint64_t UHresult =((uint64_t) (result & 0xFFFFFFFF00000000) ) >> 32;
	uint32_t LHresult = (uint32_t)(result & 0xFFFFFFFF);
	reg.regHI = uint32_t(UHresult);
	reg.regLO = LHresult;
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Unsigned Multiply " << std::endl;
	debug <<  "R" << r_operands[0] << " * R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "HI = " << reg.regHI << " LO = " << reg.regLO << std::endl;

	return 1;
}

std::uint32_t Simulator::div(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	if(B!=0){
		int32_t quotient = A/B;
		int32_t remainder = A%B; 

		reg.regHI = uint32_t(remainder);
		reg.regLO = uint32_t(quotient);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Divide " << std::endl;
		debug <<  "R" << r_operands[0] << " / R" << r_operands[1] << " = " <<std :: endl;
		debug <<  "HI(remainder) = " << reg.regHI << " LO(quotient) = " << reg.regLO << std::endl;
	}
	else{
		exit(-10);
	}

	return 1;
}

std::uint32_t Simulator::divu(){	// Cornell says that we have to sign extend Q and R Not too sure what it means since they are both 32 bits alr
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	if(B!=0){
		uint32_t quotient = A/B;
		uint32_t remainder = A%B; 

		reg.regHI = remainder;
		reg.regLO = quotient;
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Unsigned Divide " << std::endl;
		debug <<  "R" << r_operands[0] << " / R" << r_operands[1] << " = " <<std :: endl;
		debug <<  "HI(remainder) = " << reg.regHI << " LO(quotient) = " << reg.regLO << std::endl;
	}
	else{
		exit(-10);
	}

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

std::uint32_t Simulator::subu(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A-B; 
	reg.write(r_operands[2],result);

	//debugging
	std:: cout << "Performing Subu " <<std:: endl;
	std::cout <<"R" << r_operands[2] << " = R" << r_operands[0] << " - R" << r_operands[1] << " = " <<std :: endl;
	std::cout << (int)reg.read(r_operands[2]) << std::endl;

	return 1;
}

std::uint32_t Simulator::bwand(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = A&B; 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise And " << std::endl;
	debug <<  "R" << r_operands[0] << " AND R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;

	return 1;
}

std::uint32_t Simulator::bwor(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = A|B; 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise OR " << std::endl;
	debug <<  "R" << r_operands[0] << " OR R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;

	return 1;
}

std::uint32_t Simulator::bwxor(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = A^B; 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise XOR " << std::endl;
	debug <<  "R" << r_operands[0] << " XOR R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;

	return 1;
}

std::uint32_t Simulator::bwnor(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = ~(A|B); 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise NOR " << std::endl;
	debug <<  "R" << r_operands[0] << " NOR R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;

	return 1;
}

std::uint32_t Simulator::slt(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	if(A<B){
		reg.write(r_operands[2],1);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than " << std::endl;
		debug <<  "R" << r_operands[0] << " is < R" << r_operands[1] << std :: endl;
		debug <<  "R" << r_operands[2]  << " = 1 " << std::endl;
	}	
	else{
		reg.write(r_operands[2],0);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than " << std::endl;
		debug <<  "R" << r_operands[0] << " is not < R" << r_operands[1] << std :: endl;
		debug <<  "R" << r_operands[2]  << " = 0 " << std::endl;
	}

	return 1;
}

std::uint32_t Simulator::sltu(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	if(A<B){
		reg.write(r_operands[2],1);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than Unsigned " << std::endl;
		debug <<  "R" << r_operands[0] << " is < R" << r_operands[1] << std :: endl;
		debug <<  "R" << r_operands[2]  << " = 1 " << std::endl;
	}	
	else{
		reg.write(r_operands[2],0);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than Unsigned " << std::endl;
		debug <<  "R" << r_operands[0] << " is not < R" << r_operands[1] << std :: endl;
		debug <<  "R" << r_operands[2]  << " = 0 " << std::endl;
	}

	return 1;
}

/**************** I TYPE ******************/
std::uint32_t Simulator::conditional_B(){
	uint32_t branchCondition = (i_operands[1]);
	if(branchCondition == 0){
		//BLTZ	
		bltz();
	}
	else if(branchCondition == 1){
		//BGEZ
		bgez();

	}
	else if(branchCondition == 16){
		//BLTZAL
		bltzal();
	
	}
	else if(branchCondition ==17){
		//BGEZAL
		bgezal();
	}
	else{
	std :: cout << "Invalid Instruction" << std:: endl;
	exit(-10);
	}

	return 1;
}

std::uint32_t Simulator :: bltz(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BLTZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS < 0){	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS <0 and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS >= 0 and Branch not Taken "  << std::endl;
	}

	return 1;	
	
}

std::uint32_t Simulator :: bgez(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BGEZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS >= 0){	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS >=0 (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS < 0 (Branch not Taken) "  << std::endl;
	}

	return 1;	
	
}

std::uint32_t Simulator :: bltzal(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BLTZAL " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS < 0){
		uint32_t return_address = pc +8;
		reg.write(31,return_address);	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS <0 and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
		debug << "Return Addr = " << return_address << std::endl;
	}
	
	else{
		debug <<"RS >= 0 and Branch not Taken "  << std::endl;
	}

	return 1;

}

std::uint32_t Simulator :: bgezal(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;
	

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BGEZAL " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS >= 0){
		uint32_t return_address = pc +8;
		reg.write(31,return_address);	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS >=0 (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
		debug << "Return Addr = " << return_address << std::endl;	
	}
	
	else{
		debug <<"RS < 0 (Branch not Taken) "  << std::endl;
	}

	return 1;
}

std::uint32_t Simulator :: beq(){
	uint32_t A = reg.read(i_operands[0]);
	uint32_t B = reg.read(i_operands[1]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BEQ" << std::endl;

	if(A == B){	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS = RT (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS != RT (Branch not Taken) "  << std::endl;
	}

	return 1;		
}

std::uint32_t Simulator :: bne(){
	uint32_t A = reg.read(i_operands[0]);
	uint32_t B = reg.read(i_operands[1]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BNE" << std::endl;

	if(A != B){	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS != RT (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS = RT (Branch not Taken) "  << std::endl;
	}

	return 1;		
}

std::uint32_t Simulator :: blez(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BLEZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS <= 0){	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS <=0 and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS > 0 and Branch not Taken "  << std::endl;
	}

	return 1;		
}

std::uint32_t Simulator :: bgtz(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BGTZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS > 0){	
		branch_address = pc + (int32_t)branchoffset;
		branch_taken = 1;

		debug <<"RS > 0 (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS <= 0 (Branch not Taken) "  << std::endl;
	}

	return 1;	
	
}

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


std::uint32_t Simulator::sb(){
	//source: rt
	//dest	: rs + imm
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	mem.write(mem_addr,reg.read(i_operands[1]),BYTE_RW);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "SB -> " << "MEM[" << mem_addr << "] = " << "R" << i_operands[1] << std::endl;
}


std::uint32_t Simulator::lb(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	//int32_t byte_data = sign_extend( mem.read(mem_addr,BYTE_RW), 8 );
	reg.write( i_operands[1], sign_extend(mem.read(mem_addr,BYTE_RW) , 8) );

	debug << reg.read(i_operands[1]) << std::endl;
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LB -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;
	
}


std::uint32_t Simulator::sh(){
	//source: rt
	//dest	: rs + imm
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	if(mem_addr%2 == 0){
		mem.write(mem_addr,reg.read(i_operands[1]),HWORD_RW);
		//debug << mem.read(mem_addr,WORD_RW) << std::endl;;
	}
	else{
		exit(-11);
	}
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "SH -> " << "MEM[" << mem_addr << "] = " << "R" << i_operands[1] << std::endl;
}


std::uint32_t Simulator::lh(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	if(mem_addr%2 == 0){
		reg.write(i_operands[1],mem.read(mem_addr,HWORD_RW));
		debug << reg.read(i_operands[1]) << std::endl;
	}
	else{
		exit(-11);
	}
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LH -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;
	
}



std::uint32_t Simulator::sw(){
	//source: rt
	//dest	: rs + imm
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	if(mem_addr%4 == 0){
		mem.write(mem_addr,reg.read(i_operands[1]));
	}
	else{
		exit(-11);
	}
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "SW -> " << "MEM[" << mem_addr << "] = " << "R" << i_operands[1] << std::endl;
}


std::uint32_t Simulator::lw(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	if(mem_addr%4 == 0){
		reg.write(i_operands[1],mem.read(mem_addr));
		debug << reg.read(i_operands[1]) << std::endl;
	}
	else{
		exit(-11);
	}
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LW -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;
	
}









