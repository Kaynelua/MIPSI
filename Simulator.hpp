#ifndef SIMULATOR_HPP
#define	SIMULATOR_HPP

#include "Memory.hpp"
#include "Register.hpp"

class Simulator{

	private:
		Memory mem;
		Register reg;

	public:
		Simulator();
		Simulator(int pc_in);
		void run();
		int pc;


};


#endif