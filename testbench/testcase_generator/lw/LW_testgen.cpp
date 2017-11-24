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
	int offset = 0;
	string dummyLine;
	string base = "";
	string filename;


	infile.open("test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >>base >> offset >> filename ){
		outfile.open(("../../LW_tc/" + filename + ".s").c_str());
		outfile_gld.open(("../../LW_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;
		//load  base base reg -> $3
		//load  dest reg -> $2
		outfile << "addi $1,$0," 	<< gld << endl;
		outfile << "addi $2,$0,1"  << endl;
		outfile << "addi $3,$0," 	<< "0x" << base[2] << base[3] << base[4] << base[5] << endl;
		outfile << "sll  $3,$3,16"  << endl;
		outfile << "addi $3,$3," 	<< "0x" << base[6] << base[7] <<  base[8] << base[9] << endl;
 		outfile << "lw   $2," 		<< offset <<"($3)" << endl;
 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "LOAD " << gld << " patrickjohncyh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














