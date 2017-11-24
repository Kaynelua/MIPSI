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
	int shiftregnum;
	string shiftregdata;
	string dummyLine;
	string filename;


	infile.open("test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> shiftregnum >> shiftregdata >> filename ){
		outfile.open(("../../SRAV_tc/" + filename + ".s").c_str());
		outfile_gld.open(("../../SRAV_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;
		
		// Set up inputreg data in input reg:
		outfile << "addi $" 	 	<< input_reg << ",$0," << 			  "0x" << input_data[2] << input_data[3] << input_data[4] << input_data[5] << endl;
		outfile << "sll  $" 		<< input_reg << ",$" << input_reg << ",16"  << endl;
		outfile << "addi $" 	 	<< input_reg << ",$" << input_reg << ",0x" << input_data[6] << input_data[7] << input_data[8] << input_data[9] << endl;
	
		//Set up shift reg data in shift reg:
		outfile << "addi $" 	 	<< shiftregnum << ",$0," << 			  "0x" << shiftregdata[2] << shiftregdata[3] << shiftregdata[4] << shiftregdata[5] << endl;
		outfile << "sll  $" 		<< shiftregnum << ",$" << shiftregnum << ",16"  << endl;
		outfile << "addi $" 	 	<< shiftregnum << ",$" << shiftregnum << ",0x" << input_data[6] << input_data[7] << input_data[8] << input_data[9] << endl;

		
		outfile << "srav  $2,$"	 << input_reg << ",$"    << shiftregnum << endl;
 		outfile << "jr   $0" << endl;
/****************************************************************/
 		outfile_gld << "SRAV " << gld << " yh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}
