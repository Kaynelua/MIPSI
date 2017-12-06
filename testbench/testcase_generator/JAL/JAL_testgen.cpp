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


	infile.open("testbench/testcase_generator/JAL/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld  >> offset_address >>  db >>  filename ){
		outfile.open(("testbench/JAL_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/JAL_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(db == "n"){
			outfile << ".word 0x0C" << offset_address << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,1" << endl;
			outfile << "jr   $0" << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,2" << endl;
			outfile << "jr   $0" << endl;
		}

		else if(db == "y"){
			outfile << ".word 0x0C" << offset_address << endl;
			outfile << "addi $2,$2,4" << endl;
			outfile << "addi $2,$2,1" << endl;
			outfile << "jr   $0" << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,2" << endl;
			outfile << "jr   $0" << endl;
		}

		else if(db == "l"){ // test whether LR is updated after jump
			outfile << ".word 0x0C" << offset_address << endl;
			outfile << "li $31,0x5989" << endl;
			outfile << "nop" << endl;
			outfile << "add $2,$0,$31" << endl;
			outfile << "jr   $0" << endl;

		}

		else if(db == "m"){ // test whether LR is updated
			outfile << ".word 0x0C" << offset_address << endl;
			outfile << "nop" << endl;
			outfile << "nop" << endl;
			outfile << "add $2,$0,$31" << endl;
			outfile << "jr   $0" << endl;

		}
/****************************************************************/
 		outfile_gld << "JAL " << gld << " yhl15";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














