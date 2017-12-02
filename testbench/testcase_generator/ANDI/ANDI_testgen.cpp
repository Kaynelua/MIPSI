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


	infile.open("testbench/testcase_generator/ANDI/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg1 >> input_data1 >> imm  >> type >> filename ){
		outfile.open(("testbench/ANDI_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/ANDI_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(type == "N"){		//basic functionality
			outfile << "addi $2, $2, 0x59DE" << endl;
			outfile << "andi $2, $2,"	<< imm	<< endl;
		}
		else if(type == "SE"){
			outfile << "li 	 $2, 0x59DE49f8" << endl;
			outfile << "andi $2, $2,"	<< imm	<< endl;
			outfile << "srl  $2, $2, 24" 		<< endl;
		}
		else if(type == "BIG"){
			outfile << "li 	 $2, 0x59DE49f8" << endl;
			outfile << "andi $2, $2,"	<< imm	<< endl;
		}

 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "ANDI " << gld << " patrickjohncyh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














