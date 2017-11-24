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


	infile.open("test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> shift_reg >> shift_data >> filename ){
		outfile.open(("../../SRLV_tc/" + filename + ".s").c_str());
		outfile_gld.open(("../../SRLV_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		outfile << "addi $" 	 	<< input_reg << ",$0," << 			  "0x" << input_data[2] << input_data[3] << input_data[4] << input_data[5] << endl;
		outfile << "sll  $" 		<< input_reg << ",$" << input_reg << ",16"  << endl;
		outfile << "addi $" 	 	<< input_reg << ",$" << input_reg << ",0x" << input_data[6] << input_data[7] << input_data[8] << input_data[9] << endl;

		outfile << "addi $" 	 	<< shift_reg << ",$0," << 			  "0x" << shift_data[2] << shift_data[3] << shift_data[4] << shift_data[5] << endl;
		outfile << "sll  $" 		<< shift_reg << ",$" << shift_reg << ",16"  << endl;
		outfile << "addi $" 	 	<< shift_reg << ",$" << shift_reg << ",0x" << shift_data[6] << shift_data[7] << shift_data[8] << shift_data[9] << endl;


		outfile << "srlv  $2,$"	 	<< input_reg << ",$" << shift_reg << endl;
 		outfile << "jr   $0" << endl;
/****************************************************************/
 		outfile_gld << "SRLV " << gld << " patrickjohncyh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}