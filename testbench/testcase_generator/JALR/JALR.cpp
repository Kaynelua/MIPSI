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
	int link_reg =0;
	string input_address;
	char db,lr;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/JALR/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_address >> link_reg >> db >> lr >> filename ){
		outfile.open(("testbench/JALR_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/JALR_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;


		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg <<  ", 0x" << input_address << endl;
		if(lr == 'y'){							// Test specifically for when input address is 0 and testing Link Register
 			outfile << "jalr $" << link_reg << " , $2" << endl;
			outfile << "add $2, $0, $"<< link_reg << endl;
			outfile << "nop" << endl;
			outfile << "jalr $" << link_reg << " ,$" << input_reg << endl;
			outfile << "nop" << endl;
			outfile << "li $2, 0x5" << endl;
			outfile <<"nop" <<endl;
			outfile << "nop" << endl;
			outfile << "nop" << endl;
			outfile << "add $2, $0, $" << link_reg << endl;
		}
		else {
			outfile << "nop" << endl;
			outfile << "jalr $" << link_reg << " ,$" << input_reg << endl;
			if(input_address == "0" && db =='y' ){
				outfile << "li $2, 0x11 " <<endl;
			}
			outfile << "nop" << endl;
			outfile << "li $2, 0x5" << endl;
			outfile <<"nop" <<endl;
			outfile << "nop" << endl;
			outfile << "nop" << endl;
		}

		outfile << "jalr $0" << endl;

/****************************************************************/
 		outfile_gld << "JALR " << gld << " yhl15";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














