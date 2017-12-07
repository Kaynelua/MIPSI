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

	string input_data ="";

	int offset = 0;
	int dest_reg = 0;

	string test_type =""; //testing for functioanltiy (true) i.e sign extend  or range (false)

	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/LH/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_data >> base_reg >> base_data >> offset >> dest_reg >> test_type >> filename ){
		outfile.open(("testbench/LH_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/LH_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(test_type == "N"){	//normal , lower 8 bits
			outfile << "addi $1,$0," << input_data << endl; //fixed instruction which will be loaded from
			outfile << "li 	 $1,0x10000002" 	   << endl;
			outfile << "lh   $2,0($1)" 			   << endl;	//load ls hword of first instruction into R2
		}

		else if(test_type == "NF"){	//normal , full 16 bit
			outfile << "addi $1,$0," << input_data << endl; //fixed instruction which will be loaded from
			outfile << "li 	 $1,0x10000002" 	   << endl;
			outfile << "lh   $3,0($1)" 			   << endl;	//load ls hword of first instruction into R2
			outfile << "srl  $2,$3,8"			   << endl;
			outfile << "addu  $2,$2,$3"			   << endl;
		}

		else if(test_type == "SE"){	//testing sign extension
			outfile << "addi $1,$0," << input_data << endl; //fixed instruction which will be loaded from
			outfile << "li 	 $1,0x10000002" 	   << endl;
			outfile << "lh   $2,0($1)" 			   << endl;	//load ls hword of first instruction into R2
			outfile << "srl  $2,$2,9"			   << endl;
		}
		else if(test_type == "RI"){ //range check invalid
			outfile << "li 	 $" << base_reg << "," << base_data << endl;
			outfile << "lh   $" << dest_reg << "," << offset    << "($" << base_reg << ")" << endl;	//load lsbyte of first instruction into R2
		}
		else if(test_type == "RV" || test_type == "AL" ){ //range check invalid or aligntment
			outfile << "li 	 $" << base_reg << "," << base_data << endl;
			outfile << "li   $2, 128" << endl;
			outfile << "lh   $" << dest_reg << "," << offset    << "($" << base_reg << ")" << endl;	//load lsbyte of first instruction into R2
		}

		else if(test_type == "IO"){
			outfile << " lui	$2,0x3000"  << endl;
			outfile << " lh 	$2,2($2)"   << endl;
		}

		
		
 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "LH " << gld << " pjc316";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














