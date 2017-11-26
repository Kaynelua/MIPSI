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

	int shift_reg = 0;
	string shift_data;

	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/SRLV/test_data.txt");



	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> shift_reg >> shift_data >> filename ){
		outfile.open(("testbench/SRLV_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/SRLV_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg <<  "," << input_data << endl;
		//Set up shift_data in shift_reg:
		outfile << "li $" 	 	<< shift_reg <<   "," << shift_data << endl;


		outfile << "srlv $2,$"		<< input_reg << ",$" << shift_reg << endl;
 		outfile << "jr   $0" << endl;
/****************************************************************/
 		outfile_gld << "SRLV " << gld << " patrickjohncyh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}