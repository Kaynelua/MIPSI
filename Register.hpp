#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <vector>

class Register{


	private:
		std::vector<int> reg_file;


	public:
		Register();
		int read(int reg_num);
		int write(int reg_num, int data); 



};

#endif