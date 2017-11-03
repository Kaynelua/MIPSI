#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "Simulator.hpp"
#include "Memory.hpp"
#include "Register.hpp"


using namespace std;



int main(int argc, char* argv[]){



	string binary_filename;
	ifstream binfile;
	vector<char> temp_bin;
	char buffer[8];

	if(argc > 1){ binary_filename = string(argv[1]); }
	binfile.open(binary_filename.c_str() ,ios::binary);

	if(!binfile.is_open()){
		cout << "File not found!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		while(binfile.read(buffer,8)){
			int i = std::stoi(buffer, nullptr, 2);
			cout << i << endl;
		}
	}
 	//Read in binary





 	Memory mem;
 	Register reg;

	mem.write(INSTR_MEM_BASE+5,5,0);

	cout << "Reg 30 : " << reg.read(30) << endl;
	reg.write(30,5);
	cout << "Reg 30 : " << reg.read(30) << endl;

	Simulator sim;
	sim.decode();




/*
	Simulator sim;

	cout << sim.pc << endl;
*/

	return 0;
}














