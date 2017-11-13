#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstdint>

#include "Simulator.hpp"
#include "Memory.hpp"
#include "Register.hpp"
#include "Debug.hpp"




using namespace std;


void read_binstring(const string& filename,vector<uint8_t>& v_inst_out){
	ifstream binfile;
	char buffer[8];
	
	binfile.open(filename.c_str() ,ios::binary);

	if(!binfile.is_open()){
		cout << "File not found!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		int i =0;
		while(binfile.read(buffer,8)){
			i++;
			uint8_t byteInst = std::stoi(buffer, nullptr, 2);
			cout << "byteInst : " << (int)byteInst << endl;
			v_inst_out.push_back(byteInst);
			if(i == 4){
				char temp[1];
				binfile.read(temp,1);
				i = 0;
			}
		}
}
}

void read_binary(const string& filename,vector<uint8_t>& v_inst_out){
	ifstream binfile;
	char buffer[1];

	binfile.open(filename.c_str() ,ios::binary);

	if(!binfile.is_open()){
		cout << "File not found!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		while(binfile.read(buffer,1)){
			uint8_t byte_inst =  buffer[0];
			//cout << int(byte_inst) << endl;
			v_inst_out.push_back(byte_inst);
		}
	}
}


int main(int argc, char* argv[]){
	Simulator sim;
	
	string binary_filename;
	vector<uint8_t> v_byte_inst;

	if(argc > 1){ binary_filename = string(argv[1]); }
	read_binstring(binary_filename,v_byte_inst); //Read in binary
	sim.load_bin(v_byte_inst);
	int ret = sim.run();

	return ret;
}
