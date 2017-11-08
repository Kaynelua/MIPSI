#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstdint>

#include "Simulator.hpp"
#include "Memory.hpp"
#include "Register.hpp"


using namespace std;



int main(int argc, char* argv[]){



	string binary_filename;
	ifstream binfile;
	vector<char> temp_bin;
	char buffer[8];
	Simulator sim;
	vector<uint32_t> vInst;

	if(argc > 1){ binary_filename = string(argv[1]); }
	binfile.open(binary_filename.c_str() ,ios::binary);

	if(!binfile.is_open()){
		cout << "File not found!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		while(binfile.read(buffer,8)){
			uint32_t byteInst = std::stoi(buffer, nullptr, 2);
			vInst.push_back(byteInst);
		}
	}
 	//Read in binary

	//mem.write(INSTR_MEM_BASE+5,5,0);
	
	sim.loadBin(vInst);
	
	sim.decode();

	return 0;
}














