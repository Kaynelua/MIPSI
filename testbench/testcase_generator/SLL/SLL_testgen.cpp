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
	int input_data = 0;
	int shamt;
	string dummyLine;
	string filename;


	infile.open("test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> shamt >> filename ){
		outfile.open(("SLL_tc/" + filename + ".s").c_str());
		outfile_gld.open(("SLL_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		outfile << "addi $" 	 << input_reg << ",$0," << input_data << endl;
		outfile << "sll  $2,$" << input_reg << ","    << shamt << endl;
 		outfile << "jr   $0" << endl;
/****************************************************************/
 		outfile_gld << "SLL " << gld << " patrickjohncyh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














