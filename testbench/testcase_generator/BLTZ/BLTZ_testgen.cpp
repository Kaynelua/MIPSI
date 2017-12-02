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
	string offset_address;
	char db;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/BLTZ/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> offset_address >> db >> filename ){
		outfile.open(("testbench/BLTZ_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/BLTZ_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;


		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg <<  ", 0x" << input_data << endl;
		outfile << "Bltz $" << input_reg << " ,0x" << offset_address << endl;
		outfile << "nop" << endl;
		outfile << "nop" << endl;
		outfile << "li $2, 0x35" << endl;
		outfile <<"nop" <<endl;
 		outfile << "jr   $0" << endl;
		
		if(db=='y'){
		
		outfile << "li $2, 167 " << endl;
		}
/****************************************************************/
 		outfile_gld << "BLTZ " << gld << " yh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














