#include "Register.hpp"


Register::Register(): reg_file(32){
	for(int i =0;i<reg_file.size(); i++){
		reg_file[i] = 0;
	}
}

int Register::read(int reg_num){
	return reg_file[reg_num];
}

int Register::write(int reg_num,int data){
	reg_file[reg_num] = data;
	return 1;
}