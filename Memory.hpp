#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>



// test with smaller sizes first
#define INSTR_MEM_LEN 100	//268435456
#define DATA_MEM_LEN  100	//1073741824


#define INSTR_MEM_BASE 0x10000000 
#define DATA_MEM_BASE  0x20000000

#define BYTE_RW	  1
#define WORD_RW	  0

class Memory{


	private:
		std::vector<unsigned char> INSTR_MEM;
		std::vector<unsigned char> DATA_MEM;

		int	read_word();
		char read_byte();

		int write_word();
		char write_byte();


	public:
		Memory();
		int read(int ADDR, bool mode = 0);
		int write(int ADDR, int DATA, bool mode = 0);
		int writeInst(int ADDR, int DATA);
	

};

#endif


//empty adddress - > exception
