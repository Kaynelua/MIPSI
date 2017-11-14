#include "Register.hpp"
#include "Debug.hpp"



Register::Register(): reg_file(32), regHI(0), regLO(0){

}

uint32_t Register::read(uint32_t reg_num){
	return reg_file[reg_num];
}

uint32_t Register::write(uint32_t reg_num,uint32_t data){
	if(reg_num!=0){ //protection for $0
		reg_file[reg_num] = data;
	}
	return 1;
}
