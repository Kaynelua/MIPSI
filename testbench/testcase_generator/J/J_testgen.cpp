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

	string offset_address;
	string db;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/J/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld  >> offset_address >>  db >>  filename ){
		outfile.open(("testbench/J_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/J_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(db == "n"){
			outfile << ".word 0x08" << offset_address << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,1" << endl;
			outfile << "jr   $0" << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,2" << endl;
			outfile << "jr   $0" << endl;
		}
		else if(db == "y"){
			outfile << ".word 0x08" << offset_address << endl;
			outfile << "addi $2,$2,4" << endl;
			outfile << "addi $2,$2,1" << endl;
			outfile << "jr   $0" << endl;
			outfile << "nop" << endl;
			outfile << "addi $2,$2,2" << endl;
			outfile << "jr   $0" << endl;
		}




/*

		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg1 <<  ", 0x" << input_data1 << endl;
		outfile << "li $" 	 	<< input_reg2 <<  ", 0x" << input_data2 << endl;
		outfile << "J $" << input_reg1 << " , $" <<input_reg2 <<" , branchoffset" << offset_address<< endl;
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
			outfile << "J $" << input_reg1 << " , $" <<input_reg2 <<" , branchoffset0000000C" <<endl;
			outfile <<"branchoffset00000020 : "<< endl <<"nop" <<endl;
			outfile <<"branchoffset00000024 : "<< endl << "li $2 , 0x57" << endl; 
			outfile << "jr   $0" << endl;
		}

		else if (db == 'c'){  // testing backward branch 1 where backward branch is not taken
			outfile <<"nop" << endl;
			outfile <<"branchoffset00000018 : "<< endl << "li $1, 0x80000043" << endl;
			outfile << "J $" << input_reg1 << " , $" <<input_reg2 <<" , branchoffset0000000C" <<endl;
			outfile <<"branchoffset00000020 : "<< endl <<"nop" <<endl;
			outfile <<"branchoffset00000024 : "<< endl << "li $2 , 0x57" << endl; 
			outfile << "jr   $0" << endl;
		}*/

/****************************************************************/
 		outfile_gld << "J " << gld << " yh";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














