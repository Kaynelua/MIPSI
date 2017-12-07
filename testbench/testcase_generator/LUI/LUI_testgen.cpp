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
	string type;


	string dummyLine;
	string base = "";
	string filename;


	infile.open("testbench/testcase_generator/LUI/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> imm  >> type >> filename ){
		outfile.open(("testbench/LUI_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/LUI_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(type == "N"){		//basic functionality
			outfile << "lui $2,"		<< imm	<< endl;
			outfile << "srl $2,$2,16" 			<< endl;
		}
		else if(type == "SP"){	//special case, should overwrite the lower 16 bits with 0
			outfile << "addi $2,$2,0x4950" 		<< endl;
			outfile << "lui  $2,"		 << imm	<< endl;
		}


 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "LUI " << gld << " pjc316";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














