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
	int input_reg1 = 0;
	string input_data1;
	int input_reg2 = 0;
	string input_data2;
	string offset_address;
	char db;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/BEQ/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg1 >> input_data1 >> input_reg2 >> input_data2 >>offset_address >> db >> filename ){
		outfile.open(("testbench/BEQ_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/BEQ_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;


		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg1 <<  ", 0x" << input_data1 << endl;
		outfile << "li $" 	 	<< input_reg2 <<  ", 0x" << input_data2 << endl;
		outfile << "beq $" << input_reg1 << " , $" <<input_reg2 <<" , branchoffset" << offset_address<< endl;
		outfile << "li $2 , 0x47" << endl;
		outfile << "branchoffset00000004 :" << endl << "nop" << endl;
		outfile << "branchoffset00000008 :" << endl << "li $2, 0x35" << endl;
		outfile << "branchoffset0000000C :"<< endl <<"nop" <<endl;
 		outfile << "jr   $0" << endl;
		
		if(db=='y'){	// testing delayed branch
			outfile << "li $2, 167 " << endl;
		}
		
		if (db == 'b'){  // testing backward branch 1 where backward branch is taken
			outfile <<"nop" << endl;
			outfile <<"branchoffset00000018 : "<< endl << "li $2, 0x80000043" << endl;
			outfile << "beq $" << input_reg1 << " , $" <<input_reg2 <<" , branchoffset0000000C" <<endl;
			outfile <<"branchoffset00000020 : "<< endl <<"nop" <<endl;
			outfile <<"branchoffset00000024 : "<< endl << "li $2 , 0x57" << endl; 
			outfile << "jr   $0" << endl;
		}

		else if (db == 'c'){  // testing backward branch 1 where backward branch is not taken
			outfile <<"nop" << endl;
			outfile <<"branchoffset00000018 : "<< endl << "li $1, 0x80000043" << endl;
			outfile << "beq $" << input_reg1 << " , $" <<input_reg2 <<" , branchoffset0000000C" <<endl;
			outfile <<"branchoffset00000020 : "<< endl <<"nop" <<endl;
			outfile <<"branchoffset00000024 : "<< endl << "li $2 , 0x57" << endl; 
			outfile << "jr   $0" << endl;
		}

/****************************************************************/
 		outfile_gld << "BEQ " << gld << " yhl15";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














