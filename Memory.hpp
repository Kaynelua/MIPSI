#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <cstdint>

// test with smaller sizes first
#define INSTR_MEM_LEN 100	//268435456
#define DATA_MEM_LEN  100	//1073741824


#define INSTR_MEM_BASE 0x1000000
#define DATA_MEM_BASE  0x2000000

#define ADDR_GETC 0x30000000
#define ADDR_PUTC 0x30000004

#define BYTE_RW	  1
#define WORD_RW	  0

class Memory{

	private:
		std::vector<uint8_t> INSTR_MEM;
		std::vector<uint8_t> DATA_MEM;

		int	read_word();
		char read_byte();

		int write_word();
		char write_byte();


	public:
		Memory();
		std::uint32_t read(int ADDR, bool mode = 0);
		std::uint32_t write(int ADDR, int DATA, bool mode = 0);
		std::uint32_t write_inst(uint32_t ADDR, uint8_t DATA);
		std::uint32_t read_inst(uint32_t ADDR);
		std::uint32_t word_read(uint32_t RADDR, const std::vector<uint8_t>& v);
	

};

#endif


//empty adddress - > exception
