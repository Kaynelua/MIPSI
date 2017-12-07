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
	int input_reg  = 0;
	int input_data = 0;
	int dest_reg   = 0;


	string dummyLine;
	string base = "";
	string filename;


	infile.open("testbench/testcase_generator/MTHI/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> dest_reg >> filename ){
		outfile.open(("testbench/MTHI_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/MTHI_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg <<  "," << input_data << endl;
		outfile << "mthi $"		<< input_reg <<						  endl;

		outfile << "li $" 	 	<< dest_reg  <<  "," << "4"		   << endl;
		outfile << "mfhi $" 	<< dest_reg	 <<	 					  endl;

		// mv into $2
		outfile << "add $2,$0,$"<< dest_reg	<< 						  endl;

 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "MTHI " << gld << " pjc316";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














