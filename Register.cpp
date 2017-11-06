#include "Register.hpp"


Register::Register(): reg_file(32){
	for(int i =0;i<reg_file.size(); i++){
		reg_file[i] = i;
	}
}

uint32_t Register::read(uint32_t reg_num){
	return reg_file[reg_num];
}

uint32_t Register::write(uint32_t reg_num,uint32_t data){
	reg_file[reg_num] = data;
	return 1;
}
