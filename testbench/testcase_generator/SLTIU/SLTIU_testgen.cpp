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


	infile.open("testbench/testcase_generator/SLTIU/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg1 >> input_data1 >> imm  >> filename ){
		outfile.open(("testbench/SLTIU_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/SLTIU_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		outfile << "li   $" 	 	<< input_reg1 	<< "," 	<< input_data1 << endl;
		outfile << "sltiu $2, $" 	<< input_reg1	<< ","	<< imm		 	<< endl;

 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "SLTIU " << gld << " pjc316";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














