#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;


int main(){

	ofstream outfile;
	ofstream outfile_gld;
	ifstream infile;

	int gld 	   = 0;
	int input_reg1  = 0;
	string input_data1;
	string imm;
	string type;


	string dummyLine;
	string base = "";
	string filename;


	infile.open("testbench/testcase_generator/ADDI/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg1 >> input_data1 >> imm  >> type >> filename ){
		outfile.open(("testbench/ADDI_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/ADDI_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(type == "N"){		//basic functionality
			outfile << "addi $2, $0,"	<< imm	<< endl;
		}
		else if(type == "SE"){
			outfile << "addi $2, $0,"	 << imm	<< endl;
			outfile << "srl  $2, $2, 25" 		<< endl;
		}
		else if(type == "OF"){
			outfile << "li   $" 	 	<< input_reg1 	<< "," 	<< input_data1 << endl;
			outfile << "addi $2, $" 	<< input_reg1	<< ","	<< imm		 	<< endl;
		}

 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "ADDI " << gld << " patrickjohncyh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














