#ifndef REGISTER_HPP
#define REGISTER_HPP
#include <cstdint>
#include <vector>

class Register{


	private:
		std::vector<uint32_t> reg_file;


	public:
		Register();
		uint32_t read(uint32_t reg_num);
		uint32_t write(uint32_t reg_num, uint32_t data); 



};

#endif
