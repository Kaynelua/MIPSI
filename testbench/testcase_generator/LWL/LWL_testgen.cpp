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


	infile.open("testbench/testcase_generator/LWL/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_data >> base_reg >> base_data >> offset >> dest_reg >> test_type >> filename ){
		outfile.open(("testbench/LWL_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/LWL_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(test_type == "N"){	//normal, reads from correct memory areas
			outfile << "addi $1,$0," << input_data 		<< endl; //fixed instruction which will be loaded from
			outfile << "li 	 $1,0x10000000" 	   		<< endl;
			outfile << "lwl  $2," << offset << "($1)" 	<< endl;	//load word of first instruction into R2
			outfile << "srl  $2,$2," << offset*8		<< endl;
		}

		else if(test_type == "DP"){		//correct data slots are preserved
			outfile << "addi $1,$0," << input_data 		 << endl; //fixed instruction which will be loaded from
			outfile << "li 	 $1,0x10000000" 	   		 << endl;
			outfile << "li   $2,0x12345678"				 << endl;
			outfile << "lwl  $2," 	 << offset << "($1)" << endl;	//load word of first instruction into R2
			if(offset > 0){
				outfile << "srl  $2,$2," << (offset-1)*8		 << endl;
			}
		}

		else if(test_type == "NSE"){	//normal, reads from correct memory areas
			outfile << "li   $3," << input_data 							<< endl; //fixed instruction which will be loaded from
			outfile << "li 	 $"	  << base_reg << ","  << base_data	   		<< endl;
			outfile << "sw   $3," << "0"      << "($" << base_reg  << ")"	<< endl;

			outfile << "lwl  $2," << offset << "($"  << base_reg  << ")" 	<< endl;	//load word of first instruction into R2
			outfile << "srl  $2,$2,"<< offset*8 + 1 << endl;
		}

		else if(test_type == "RI"){ //range check invalid
			outfile << "li 	 $" << base_reg << "," << base_data << endl;
			outfile << "LWL   $" << dest_reg << "," << offset    << "($" << base_reg << ")" << endl;	//load lsbyte of first instruction into R2
		}
		else if(test_type == "RV" || test_type == "AL" ){ //range check invalid or aligntment
			outfile << "li 	 $" << base_reg << "," << base_data << endl;
			outfile << "li   $2, 128" << endl;
			outfile << "LWL   $" << dest_reg << "," << offset    << "($" << base_reg << ")" << endl;	//load lsbyte of first instruction into R2
		}
		
		
 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "LWL " << gld << " pjc316";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














