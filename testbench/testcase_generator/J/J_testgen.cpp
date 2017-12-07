#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;


int main(){

	ofstream outfile;
	ofstream outfile_gld;
	ifstream infile;

	int gld  = 0;

	string offset_address;
	string db;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/J/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld  >> offset_address >>  db >>  filename ){
		outfile.open(("testbench/J_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/J_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(db == "n"){
			outfile << ".word 0x08" << offset_address << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,1" << endl;
			outfile << "jr   $0" << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,2" << endl;
			outfile << "jr   $0" << endl;
		}
		else if(db == "y"){
			outfile << ".word 0x08" << offset_address << endl;
			outfile << "addi $2,$2,4" << endl;
			outfile << "addi $2,$2,1" << endl;
			outfile << "jr   $0" << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,2" << endl;
			outfile << "jr   $0" << endl;
		}
		else if(db == "i"){//Invalid Address
			outfile << ".word 0x0" << offset_address << endl;
			outfile << "addi $2,$2,4" << endl;
			outfile << "addi $2,$2,1" << endl;
			outfile << "jr   $0" << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,2" << endl;
			outfile << "jr   $0" << endl;
		}



/****************************************************************/
 		outfile_gld << "J " << gld << " yhl15";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














