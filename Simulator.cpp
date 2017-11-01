/*
 * Simulator.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: kayne
 */

#include "Simulator.hpp"
#include <iostream>


Simulator::Simulator(){
	pc = 4;
}

Simulator::Simulator(int pc_in){
	pc = pc_in;
}

void Simulator::run(){
	std::cout << "current pc val : " << pc << std::endl;
}

void Simulator :: setInstAndType(int binInst){
	Inst = binInst;
	opcode = ((Inst & OPMASK) >> 26);

	if(opcode == 0){
		std:: cout << "R-type" << std::endl;
		instType = 0;
	}
	else if( opcode == 2 || opcode ==3 ){
		std:: cout << "J-type" << std:: endl;
		instType = 1;
	}
	else{
		std:: cout << "I-type" << std :: endl;
		instType = 2;
	}

}

void Simulator :: setFieldandFlag(){
	if(instType == 0){ 		//R-type
		Rsource1 = (Inst & S1MASK) >> 21;
		Rsource2 = (Inst & S2MASK) >> 16;
		Rdest = (Inst & RDMASK) >> 11;
		Rshift = (Inst & RSHMASK) >> 6;
		RFunct = (Inst & RFMASK);
	}
	else if(instType == 1){ 	// I-type
		Isource1 = (Inst & S1MASK) >> 21;
		Isource2 = (Inst & S2MASK) >> 16;
		Idata = (Inst & IDMASK);
	}
	else if(instType == 2){		// J-type
		Jaddress = (Inst & JAMASK);
	}
}
