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

void Simulator::stub(){
	exit(INVALID_INSTRUCTION);
}

/**************** J TYPE ******************/
void Simulator::j(){
	branch_address = (j_operands[0]*4);
	branch_address = (branch_address | ((pc+4)&0xF0000000) );
	branch_taken = 1;
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump (PC):" << j_operands[0]*4 << std::endl;
}

void Simulator::jal(){
	branch_address = (j_operands[0]*4);
	branch_address = (branch_address | ((pc+4)&0xF0000000) );
	branch_taken = 1;

	uint32_t return_address = pc +8;
	
	link  = 1;
	link_register = 31;
	link_address = return_address;

	reg.write(31,return_address);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump and Link (PC): Branch Target=" << branch_address << std::endl;
	debug <<"RETURN ADDR IN R31 = " << return_address << std::endl;
}


/**************** R TYPE ******************/

void Simulator::sll(){
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt << shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] <<" = R" << r_operands[1] << " Shift left Logical by " << shiftamt << std::endl;
}

void Simulator::srl(){
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] <<" = R" << r_operands[1] << " Shift Right Logical by " << shiftamt << std::endl;
}

void Simulator::sra(){ 
	uint32_t shiftamt = r_operands[3];
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = (int32_t)rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] <<" = R" << r_operands[1] << " Shift Right Arithmetic by " << shiftamt << std::endl;
}

void Simulator::sllv(){
	uint32_t shiftamt = ( reg.read(r_operands[0]) & 0x1F );
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt << shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] << " = R" <<r_operands[1] << " Shift left Logical Variable by " << shiftamt << std::endl;
}

void Simulator::srlv(){
	uint32_t shiftamt = ( reg.read(r_operands[0]) & 0x1F );
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] << " = R" <<r_operands[1] << " Shift Right Logical Variable by " << shiftamt << std::endl;
}

void Simulator::srav(){
	uint32_t shiftamt = ( reg.read(r_operands[0]) & 0x1F );
	uint32_t rt = reg.read(r_operands[1]);
	uint32_t rd = (int32_t)rt >> shiftamt;
	reg.write(r_operands[2],rd);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : R" << r_operands[2] << " = R" <<r_operands[1] << " Shift Right Arithmetic Variable by " << shiftamt << std::endl;
	debug << "shiftam : " << shiftamt << ", rt: " << rt <<  ", rd : "<< rd << std::endl;
}

void Simulator::jr(){	// JUMPING to invalid PC INSTRUCTION ADDRESS
	uint32_t jd = reg.read(r_operands[0]);
	
	if(jd%4 == 0){
		branch_address = jd;
		branch_taken = 1;
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump Register (PC) -> " << jd << std::endl;
	}
	else{
		exit(-11);
	}
}

void Simulator::jalr(){ 
	uint32_t jd = reg.read(r_operands[0]);
	uint32_t return_address = pc +8;

	if(jd%4 == 0){
		link_address  = return_address;
		link_register = r_operands[2];
		link = 1;
		branch_address = jd;
		branch_taken = 1;
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Jump Register (PC) -> " << jd << std::endl;
		debug <<"RETURN ADDR IN R" << r_operands[2] << " = "  << return_address << std::endl;
	}
	else{
		exit(-11);
	}
}

void Simulator::mfhi(){	// UNHANDLED: Reads of HI/LO Register must be separated from any instructions that writes to them by 2 or more
	
	int32_t data =  reg.regHI;
	reg.write(r_operands[2],data);
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move From HI " << std::endl;
	debug << "R" << r_operands[2] << " = " << reg.read(r_operands[2])  << std::endl;
}

void Simulator::mthi(){
	
	int32_t data =  reg.read(r_operands[0]);
	reg.regHI = data;
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move TO HI " << std::endl;
	debug << "reg HI = R"  << r_operands[0] << " = " << data << std::endl;
}

void Simulator::mflo(){
	
	int32_t data =  reg.regLO;
	reg.write(r_operands[2],data);
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move From LO " << std::endl;
	debug << "R" << r_operands[2] << " = " << reg.read(r_operands[2])  << std::endl;
}

void Simulator::mtlo(){
	
	int32_t data =  reg.read(r_operands[0]);
	reg.regLO = data;
	//debugging
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Move TO LO " << std::endl;
	debug << "reg LO = R"  << r_operands[0] << " = " << data << std::endl;
}

void Simulator::mult(){
	
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
}

void Simulator::multu(){	// NOT QUITE SURE WHAT UNSIGNED MULTIPLY MEANS /DIFFER OTHER THAN OPERANDS BEING UNSIGNED
	
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
}

void Simulator::div(){
	
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
	// If Divisor is 0 , Undefined behavior and we leave State as it is.
}

void Simulator::divu(){	// Cornell says that we have to sign extend Q and R Not too sure what it means since they are both 32 bits alr
	
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
	// If Divisor is 0 , Undefined behavior and we leave State as it is.
}


void Simulator::add(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A+B; 
	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<0) && (B<0) && (result >=0)) ){
		exit(-10);
	}

	//debugging
	debug << "Performing Add " <<std:: endl;
	debug <<"R" << r_operands[2] << " = R" << r_operands[0] << " + R" << r_operands[1] << " = " <<std :: endl;
	reg.write(r_operands[2],result);

	debug << reg.read(r_operands[2]) << std::endl;
}

void Simulator::addu(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A+B; 
	reg.write(r_operands[2],result);
	//debugging
	debug << "Performing Addu " <<std:: endl;
	debug <<"R" << r_operands[2] << " = R" << r_operands[0] << " + R" << r_operands[1] << " = " <<std :: endl;
	debug << reg.read(r_operands[2]) << std::endl;
}

void Simulator::sub(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A-B; 
	reg.write(r_operands[2],result);
	if( ((A >= 0) && (B< 0) && (result < 0)) || ((A<0) && (B>=0) && (result >=0)) ){
		exit(-10);
	}
	//debugging
	debug << "Performing Sub " <<std:: endl;
	debug <<"R" << r_operands[2] << " = R" << r_operands[0] << " - R" << r_operands[1] << " = " <<std :: endl;
	debug << (int)reg.read(r_operands[2]) << std::endl;
}

void Simulator::subu(){
	
	int32_t A =  reg.read(r_operands[0]);
	int32_t B =  reg.read(r_operands[1]);
	int32_t result = A-B; 
	reg.write(r_operands[2],result);

	//debugging
	debug  << "Performing Subu " <<std:: endl;
	debug <<"R" << r_operands[2] << " = R" << r_operands[0] << " - R" << r_operands[1] << " = " <<std :: endl;
	debug << (int)reg.read(r_operands[2]) << std::endl;
}

void Simulator::bwand(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = A&B; 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise And " << std::endl;
	debug <<  "R" << r_operands[0] << " AND R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;
}

void Simulator::bwor(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = A|B; 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise OR " << std::endl;
	debug <<  "R" << r_operands[0] << " OR R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;
}

void Simulator::bwxor(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = A^B; 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise XOR " << std::endl;
	debug <<  "R" << r_operands[0] << " XOR R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;
}

void Simulator::bwnor(){
	
	uint32_t A =  reg.read(r_operands[0]);
	uint32_t B =  reg.read(r_operands[1]);
	uint32_t result = ~(A|B); 
	reg.write(r_operands[2],result);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Bitwise NOR " << std::endl;
	debug <<  "R" << r_operands[0] << " NOR R" << r_operands[1] << " = " <<std :: endl;
	debug <<  "R" << r_operands[2]  << " = " << result << std::endl;
}

void Simulator::slt(){
	
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
}

void Simulator::sltu(){
	
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
}

/**************** I TYPE ******************/
void Simulator::conditional_B(){
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
}

void Simulator::bltz(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BLTZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS < 0){	
		branch_address = pc + (int32_t)branchoffset + 4;
		branch_taken = 1;

		debug <<"RS <0 and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS >= 0 and Branch not Taken "  << std::endl;
	}	
}

void Simulator::bgez(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BGEZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS >= 0){	
		branch_address = pc + (int32_t)branchoffset +4;
		branch_taken = 1;

		debug <<"RS >=0 (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS < 0 (Branch not Taken) "  << std::endl;
	}

}

void Simulator::bltzal(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BLTZAL " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS < 0){
		uint32_t return_address = pc +8;
		branch_address = pc + (int32_t)branchoffset + 4;
		branch_taken = 1;
		
		link_address  = return_address;
		link_register = 31;
		link = 1;

		debug <<"RS <0 and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
		debug << "Return Addr = " << return_address << std::endl;
	}
	
	else{
		debug <<"RS >= 0 and Branch not Taken "  << std::endl;
	}

}

void Simulator::bgezal(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;
	

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BGEZAL " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS >= 0){
		uint32_t return_address = pc +8;	
		branch_address = pc + (int32_t)branchoffset + 4;
		branch_taken = 1;
		
		link_address  = return_address;
		link_register = 31;
		link = 1;

		debug <<"RS >=0 (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
		debug << "Return Addr = " << return_address << std::endl;	
	}
	
	else{
		debug <<"RS < 0 (Branch not Taken) "  << std::endl;
	}

}

void Simulator::beq(){
	uint32_t A = reg.read(i_operands[0]);
	uint32_t B = reg.read(i_operands[1]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BEQ" << std::endl;

	if(A == B){	
		branch_address = pc + (int32_t)branchoffset + 4;
		branch_taken = 1;

		debug <<"RS = RT (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS != RT (Branch not Taken) "  << std::endl;
	}
		
}

void Simulator::bne(){
	uint32_t A = reg.read(i_operands[0]);
	uint32_t B = reg.read(i_operands[1]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BNE" << std::endl;

	if(A != B){	
		branch_address = pc + (int32_t)branchoffset + 4;
		branch_taken = 1;

		debug <<"RS != RT (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS = RT (Branch not Taken) "  << std::endl;
	}
		
}

void Simulator::blez(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BLEZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS <= 0){	
		branch_address = pc + (int32_t)branchoffset + 4;
		branch_taken = 1;

		debug <<"RS <=0 and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS > 0 and Branch not Taken "  << std::endl;
	}	
}

void Simulator::bgtz(){
	int32_t RS = reg.read(i_operands[0]);
	int32_t branchoffset =  sign_extend(i_operands[2],16) *4 ;

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "BGTZ " << std::endl;
	debug <<"R" << i_operands[0] << " = " << RS << std::endl;

	if(RS > 0){	
		branch_address = pc + (int32_t)branchoffset + 4;
		branch_taken = 1;

		debug <<"RS > 0 (Branch Taken) and Branch Offset = " << branchoffset << " PC Target = " << branch_address  << std::endl;
	}
	
	else{
		debug <<"RS <= 0 (Branch not Taken) "  << std::endl;
	}	
	
}

void Simulator::addi(){
	//source : rs,imm
	//dest : rt
	int32_t A = reg.read(i_operands[0]);
	int32_t B = sign_extend(i_operands[2],16);
	int32_t result = A+B;
	if( ((A >= 0) && (B>= 0) && (result < 0)) || ((A<0) && (B<0) && (result >=0)) ){
		debug << "Signed Overflow Exception code" << std:: endl;
		exit(-10);
	}
	reg.write(i_operands[1],result);

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "ADDI :" << "R" << i_operands[1] << "= R"<<i_operands[0] << " + " <<  i_operands[2]<< std::endl;
	debug << reg.read(i_operands[1]) <<std::endl;

}

void Simulator::addiu(){
	//source : rs,imm
	//dest : rt
	int32_t A = reg.read(i_operands[0]);
	int32_t B = sign_extend(i_operands[2],16);
	int32_t result = A+B;
	reg.write(i_operands[1],result);

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "ADDIU :" << "R" << i_operands[1] << "= R"<<i_operands[0] << " + " << B << std::endl;

}

void Simulator::slti(){
	
	int32_t RS =  reg.read(i_operands[0]);
	int32_t Immediate =  sign_extend(i_operands[2],16);

	if(RS < Immediate){
		reg.write(i_operands[1],1);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than Immediate " << std::endl;
		debug <<  "R" << i_operands[0] << " is < Immediate = " << Immediate << std :: endl;
		debug <<  "R" << i_operands[1]  << " = 1 " << std::endl;
	}	
	else{
		reg.write(i_operands[1],0);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than Immediate" << std::endl;
		debug <<  "R" << i_operands[0] << " is not < Immediate = " << Immediate << std :: endl;
		debug <<  "R" << i_operands[1]  << " = 0 " << std::endl;
	}

}

void Simulator::sltiu(){
	
	uint32_t RS =  reg.read(i_operands[0]);
	uint32_t Immediate =  sign_extend(i_operands[2],16);

	if(RS < Immediate){
		reg.write(i_operands[1],1);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than Immediate Unsigned" << std::endl;
		debug <<  "R" << i_operands[0] << " is < Immediate = " << Immediate << std :: endl;
		debug <<  "R" << i_operands[1]  << " = 1 " << std::endl;
	}	
	else{
		reg.write(i_operands[1],0);
		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "Set less than Immediate Unsigned" << std::endl;
		debug <<  "R" << i_operands[0] << " is not < Immediate = " << Immediate << std :: endl;
		debug <<  "R" << i_operands[1]  << " = 0 " << std::endl;
	}
}

void Simulator::andi(){
	
	uint32_t RS =  reg.read(i_operands[0]);
	uint32_t Immediate =  i_operands[2];
	uint32_t result = Immediate & RS;
	reg.write(i_operands[1],result);

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "And Immediate " << std::endl;
	debug <<  "R" << i_operands[0] << " AND Immediate " << i_operands[2] << " = " <<std :: endl;
	debug <<  "R" << i_operands[1]  << " = " << result << std::endl;
}

void Simulator::ori(){
	
	uint32_t RS =  reg.read(i_operands[0]);
	uint32_t Immediate =  i_operands[2];
	uint32_t result = Immediate | RS;
	reg.write(i_operands[1],result);

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "OR Immediate " << std::endl;
	debug <<  "R" << i_operands[0] << " OR Immediate " << i_operands[2] << " = " <<std :: endl;
	debug <<  "R" << i_operands[1]  << " = " << result << std::endl;
}

void Simulator::xori(){
	
	uint32_t RS =  reg.read(i_operands[0]);
	uint32_t Immediate =  i_operands[2];
	uint32_t result = Immediate ^ RS;
	reg.write(i_operands[1],result);

	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "XOR Immediate " << std::endl;
	debug <<  "R" << i_operands[0] << " XOR Immediate " << i_operands[2] << " = " <<std :: endl;
	debug <<  "R" << i_operands[1]  << " = " << result << std::endl;
}


void Simulator::sb(){
	//source: rt
	//dest	: rs + imm
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	mem.write(mem_addr,reg.read(i_operands[1]),BYTE_RW);
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "SB -> " << "MEM[" << mem_addr << "] = " << "R" << i_operands[1] << std::endl;
}


void Simulator::lb(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	//int32_t byte_data = sign_extend( mem.read(mem_addr,BYTE_RW), 8 );
	reg.write( i_operands[1], sign_extend(mem.read(mem_addr,BYTE_RW) , 8) );

	debug << reg.read(i_operands[1]) << std::endl;
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LB -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;
	
}


void Simulator::sh(){
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


void Simulator::lh(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	if(mem_addr%2 == 0){
		reg.write(i_operands[1], sign_extend( mem.read(mem_addr,HWORD_RW) , 16) );
		debug << reg.read(i_operands[1]) << std::endl;
	}
	else{
		exit(-11);
	}
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LH -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;
	
}



void Simulator::sw(){
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


void Simulator::lw(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	debug << "mem addr " <<(int32_t)reg.read(i_operands[0]) << std::endl;
	if(mem_addr%4 == 0){

		debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LW -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;	
		reg.write(i_operands[1],mem.read(mem_addr));
		debug << reg.read(i_operands[1]) << std::endl;
	}
	else{
		exit(-11);
	}
}


void Simulator::lwl(){	//need to check for address error

	int32_t eff_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);	//unaligned access permissible



	uint32_t rt_data = reg.read(i_operands[1]);


	uint32_t remainder = eff_addr%4;
	uint32_t aligned_addr = eff_addr-remainder;
	uint32_t aligned_word = mem.read(aligned_addr,WORD_RW);
	//extract least significant (4-r) bytes and assign to MS 4-r bytes of rt_data
	uint32_t word_mask = 0xFFFFFFFF;
	uint32_t rt_data_mask = 0xFFFFFFFF;

	word_mask = word_mask >> remainder*8;
	rt_data_mask = rt_data_mask >> (4-remainder)*8;
	if(remainder == 0){
		rt_data_mask = 0;
	}

	aligned_word = (aligned_word & word_mask) << remainder*8;
	rt_data = (rt_data & rt_data_mask);
	rt_data = rt_data | aligned_word;

	reg.write(i_operands[1],rt_data);

	debug << std::setw(21)  << std::left << "INSTRUCTION" << " : " << "LWL -> " << std:: endl;
}

void Simulator::lwr(){	//need to check for address error


	int32_t eff_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);	//unaligned access permissible

	uint32_t rt_data = reg.read(i_operands[1]);

	uint32_t remainder = eff_addr%4;
	uint32_t aligned_addr = eff_addr-remainder;
	uint32_t aligned_word = mem.read(aligned_addr,WORD_RW);


	//extract most significant r bytes and assign to LS r bytes of rt_data
	uint32_t word_mask = 0xFFFFFFFF;
	uint32_t rt_data_mask = 0xFFFFFFFF;

	word_mask = word_mask << (3-remainder)*8;
	rt_data_mask = rt_data_mask << (remainder+1)*8;
	if(remainder == 3){		//sepcial case since range of shift is only from 0 - 31!! c++ limits or isit x86?
		rt_data_mask = 0;
	}

	debug << "word mask! ! : " << word_mask << std::endl;
	debug << "rt_data mask! ! : " << rt_data_mask << std::endl;


	aligned_word = (aligned_word & word_mask) >> (3-remainder)*8;
	rt_data = (rt_data & rt_data_mask);
	rt_data = rt_data | aligned_word;

	reg.write(i_operands[1],rt_data);

	debug << rt_data << std::endl;

	debug << std::setw(21)  << std::left << "INSTRUCTION" << " : " << "LWR -> " << std:: endl;
}


void Simulator::lbu(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	//int32_t byte_data = sign_extend( mem.read(mem_addr,BYTE_RW), 8 );
	reg.write( i_operands[1], mem.read(mem_addr,BYTE_RW) );

	debug << reg.read(i_operands[1]) << std::endl;
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LBU -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;
}

void Simulator::lhu(){
	//source: rs,imm
	//dest	: rt
	int32_t mem_addr = (int32_t)reg.read(i_operands[0]) + sign_extend(i_operands[2],16);
	if(mem_addr%2 == 0){
		reg.write(i_operands[1], mem.read(mem_addr,HWORD_RW) );
		debug << reg.read(i_operands[1]) << std::endl;
	}
	else{
		exit(-11);
	}
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LHU -> " << "R" << i_operands[1] << " = MEM[" << mem_addr << "]" << std::endl;
	
}

void Simulator::lui(){
	//source : imm
	//dest	 : rt
	reg.write( i_operands[1], (i_operands[2] << 16) | 0x00000000 );
	debug << std::setw(21)  << std::left <<"INSTRUCTION" << " : " << "LUI " << std::endl;
	debug << "R" << i_operands[1] << " = " << ((i_operands[2] << 16) | 0x00000000)  << std::endl;
}





