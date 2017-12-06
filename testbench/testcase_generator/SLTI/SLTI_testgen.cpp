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


	string dummyLine;
	string base = "";
	string filename;


	infile.open("testbench/testcase_generator/SLTI/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg1 >> input_data1 >> imm  >> filename ){
		outfile.open(("testbench/SLTI_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/SLTI_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		outfile << "li   $" 	 	<< input_reg1 	<< "," 	<< input_data1 << endl;
		outfile << "slti $2, $" 	<< input_reg1	<< ","	<< imm		 	<< endl;

 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "SLTI " << gld << " yhl15";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














