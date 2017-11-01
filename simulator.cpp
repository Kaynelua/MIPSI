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