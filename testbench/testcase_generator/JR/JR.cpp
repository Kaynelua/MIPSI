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
	string input_address;
	char db;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/JR/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_address >> db >> filename ){
		outfile.open(("testbench/JR_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/JR_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;


		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg <<  ", 0x" << input_address << endl;
		outfile << "nop" << endl;
		if(input_address != "0"){
			outfile << "jr $" << input_reg << endl;
			outfile << "nop" << endl;
			outfile << "li $2, 0x5" << endl;
			outfile <<"nop" <<endl;
		}

 		outfile << "jr   $0" << endl;
		
		if(db=='y'){
		
		outfile << "li $2, 157 " << endl;
		}
/****************************************************************/
 		outfile_gld << "JR " << gld << " yhl15";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














