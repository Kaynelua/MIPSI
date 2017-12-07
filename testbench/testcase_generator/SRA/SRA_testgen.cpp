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
	int input_reg = 0;
	string input_data;
	int shamt;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/SRA/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> shamt >> filename ){
		outfile.open(("testbench/SRA_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/SRA_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg <<  "," << input_data << endl;

		outfile << "sra  $2,$"	 << input_reg << ","    << shamt << endl;
 		outfile << "jr   $0" << endl;
/****************************************************************/
 		outfile_gld << "SRA " << gld << " pjc316";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}
