#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;


int main(){

	ofstream outfile;
	ofstream outfile_gld;
	ifstream infile;

	string gld;
	int base_reg=0;
	string base_data = "";

	string input_data ="";

	int offset = 0;
	int dest_reg = 0;

	string test_type =""; //testing for functioanltiy (true) i.e sign extend  or range (false)

	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/SB/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_data >> base_reg >> base_data >> offset >> dest_reg >> test_type >> filename ){
		outfile.open(("testbench/SB_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/SB_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;

		if(test_type == "N" || test_type == "RV"){	//testing basic functionality
			outfile << "li 	 $"				<< base_reg << ","						<< base_data		<< endl;
			outfile << "sb   $" 			<< base_reg << ","	<<  offset << "($"	<< base_reg  << ")"	<< endl;
			outfile << "lb   $2," 			<< offset   << "($"	<< base_reg << ")"						<< endl;

		}
		else if(test_type == "SE"){	//testing basic functionality and special cases
			outfile << "addi $1,$0," << input_data << endl; //fixed instruction which will be loaded from
			outfile << "li 	 $1,0x10000003" 	   << endl;
			outfile << "sb   $2,0($1)" 			   << endl;	//load lsbyte of first instruction into R2
			outfile << "srl  $2,$2,1"			   << endl;
		}
		else if(test_type == "RI"){ //range check invalid
			outfile << "li 	 $" << base_reg << "," << base_data << endl;
			outfile << "sb   $" << dest_reg << "," << offset    << "($" << base_reg << ")" << endl;	//load lsbyte of first instruction into R2
		}

		else if(test_type == "PUTC"){ //range check invalid
			outfile << "li 	 $" << dest_reg << "," << input_data << endl;
			outfile << "li 	 $" << base_reg << "," << base_data << endl;
			outfile << "sb   $" << dest_reg << "," << offset    << "($" << base_reg << ")" << endl;
		}
		
 		outfile << "jr   $0" 		<< endl;
/****************************************************************/
 		outfile_gld << "SB " << gld << " pjc316";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














