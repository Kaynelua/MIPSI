#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;


int main(){

	ofstream outfile;
	ofstream outfile_gld;
	ifstream infile;

	int gld  = -0;
	string base = "";
	int offset = 0;
	int dest_reg = 0;

	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/LW/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> base >> offset >> dest_reg >> filename ){
		outfile.open(("testbench/LW_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/LW_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;


		outfile << "addi $1,$0," 	<< gld << endl;



 		outfile << "lw   $2," 		<< offset <<"($3)" << endl;
 		outfile << "jal   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "LOAD " << gld << " patrickjohncyh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














