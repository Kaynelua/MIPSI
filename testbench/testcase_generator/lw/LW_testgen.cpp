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
	int base_reg=0;
	string base_data = "";
	int offset = 0;
	int dest_reg = 0;

	bool func = false; //testing for functioanltiy (true) i.e sign extend  or range (false)

	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/LW/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> base_reg >> base_data >> offset >> dest_reg >> filename ){
		outfile.open(("testbench/LW_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/LW_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(func){
			outfile << "addi $1,$0," 		<< gld << endl; //fixed instruction which will be loaded from
			outfile << "li 	 $1,0x10000000" 	   << endl;
			outfile << "lw   $3,0($1)" 			   << endl;	//load first instruction in mem into R2

			
			

			outfile << "li 	 $3,0x20000000" 	   				<< endl;
			outfile << "li 	 $4,0x00010000" 	  				<< endl;
			outfile << "li 	 $5," << (gld & 0x00001100)			<< endl;
			outfile << "li 	 $6," << (gld & 0x00000011)			<< endl;




		}

		



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














