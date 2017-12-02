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
	int input_reg2 = 0;
	string input_data2;
	char testHL;


	string dummyLine;
	string base = "";
	string filename;


	infile.open("testbench/testcase_generator/DIVU/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg1 >> input_data1 >> input_reg2 >> input_data2 >> testHL>> filename ){
		outfile.open(("testbench/DIVU_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/DIVU_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		//outfile << ".set noat" 		<< endl;

		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg1 <<  ", 0x" << input_data1 << endl;
		outfile << "li $" 	 	<< input_reg2  <<  ", 0x" <<  input_data2    << endl;
		outfile << "divu $" 	<< input_reg1	 << ", $" <<input_reg2 	<<		  endl;
		
		// mv from hi or low into $2 to test
		
		if(testHL == 'h'){
			outfile << "mfhi $2 " <<   endl;
		}
		else if(testHL == 'l'){
			outfile << "mflo $2 " << endl;
		}
	
 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "DIVU " << gld << " yh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














