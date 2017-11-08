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
	char buffer[8];
	vector<uint8_t> vInst;

	Simulator sim;


	if(argc > 1){ binary_filename = string(argv[1]); }
	binfile.open(binary_filename.c_str() ,ios::binary);

	if(!binfile.is_open()){
		cout << "File not found!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		int i =0;
		while(binfile.read(buffer,8)){
			i++;
			uint8_t byteInst = std::stoi(buffer, nullptr, 2);
			//cout << "byteInst : " << (int)byteInst << endl;
			vInst.push_back(byteInst);
			if(i == 4){
				char temp[1];
				binfile.read(temp,1);
				i = 0;
			}
		}
	}

 	//Read in binary

	sim.load_bin(vInst);
	return sim.run();

	//return 0;
}














