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
	string input_data;
	string offset_address;
	char db;
	string dummyLine;
	string filename;


	infile.open("testbench/testcase_generator/BGEZAL/test_data.txt");

	getline(infile, dummyLine);
	while(infile >> gld >> input_reg >> input_data >> offset_address >> db >> filename ){
		outfile.open(("testbench/BGEZAL_tc/" + filename + ".s").c_str());
		outfile_gld.open(("testbench/BGEZAL_tc/" + filename + ".mips.gld").c_str());


/****************************************************************/
		outfile << ".set noreorder" << endl;
		outfile << ".set noat" 		<< endl;


		// Set up input_data in input_reg:
		outfile << "li $" 	 	<< input_reg <<  ", 0x" << input_data << endl;
		outfile << "bgezal $" << input_reg << " , branchoffset" << offset_address<< endl;
		if(db== 'l') { // testing when link register is updated
			outfile << "nop" << endl;
			outfile << "branchoffset00000004 :" << endl << "nop" << endl;
			outfile << "branchoffset00000008 :" << endl << "add $2,$0,$31" << endl;
			outfile << "branchoffset0000000C :"<< endl <<"nop" <<endl;
 			outfile << "jr   $0" << endl;
			outfile << "nop" <<endl;
		}
		else{
			outfile << "li $" << input_reg << " , 0x47" << endl;
			outfile << "branchoffset00000004 :" << endl << "nop" << endl;
			outfile << "branchoffset00000008 :" << endl << "li $2, 0x35" << endl;
			outfile << "branchoffset0000000C :"<< endl <<"nop" <<endl;
 			outfile << "jr   $0" << endl;
		}
		
		
		if(db=='y'){	// testing delayed branch
		outfile << "li $2, 167 " << endl;
		}
	
		
		if (db == 'b'){  // testing backward branch 1 where backward branch is not taken
		outfile <<"nop" << endl;
		outfile <<"branchoffset00000018 : "<< endl << "li $" << input_reg << ", 0x80000043" << endl;
		outfile <<"branchoffset0000001C : " << endl << "bgezal $" << input_reg << " , branchoffset0000000C" <<endl;
		outfile <<"branchoffset00000020 : "<< endl <<"nop" <<endl;
		outfile <<"branchoffset00000024 : "<< endl << "li $" << input_reg << ", 0x57" << endl; 
		outfile << "jr   $0" << endl;
		}

		else if (db == 'c'){  // testing backward branch 2 where backward branch taken
		outfile <<"nop" << endl;
		outfile <<"branchoffset00000018 : "<< endl << "li $" << input_reg << ", 0x70000048" << endl;
		outfile <<"branchoffset0000001C : " << endl << "bgezal $" << input_reg << " , branchoffset0000000C" <<endl;
		outfile <<"branchoffset00000020 : "<< endl <<"nop" <<endl;
		outfile <<"branchoffset00000024 : "<< endl << "li $" << input_reg << ", 0x57" << endl; 
		outfile << "jr   $0" << endl;
		}

/****************************************************************/
 		outfile_gld << "BGEZAL " << gld << " yhl15";

/****************************************************************/ 		


 		outfile_gld.close();
		outfile.close();
	}
	return 0;
}














