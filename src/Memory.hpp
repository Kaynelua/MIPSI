#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <cstdint>

// test with smaller sizes first
#define INSTR_MEM_LEN 0x1000000	//268435456
#define DATA_MEM_LEN  0x4000000	//1073741824


#define INSTR_MEM_BASE 0x10000000
#define DATA_MEM_BASE  0x20000000

#define ADDR_GETC 0x30000000
#define ADDR_GETC_HW 0x30000002
#define ADDR_GETC_B 0x30000003

#define ADDR_PUTC 0x30000004
#define ADDR_PUTC_HW 0x30000006
#define ADDR_PUTC_B 0x30000007

#define BYTE_RW	  2
#define HWORD_RW  1
#define WORD_RW	  0


#define INVALID_INSTRUCTION -12
#define MEMORY_EXCEPTION	-11
#define ARITHMETIC_EXCEPTION -10

class Memory{

	private:
		std::vector<uint8_t> INSTR_MEM;
		std::vector<uint8_t> DATA_MEM;


		std::uint32_t half_word_read(uint32_t RADDR, const std::vector<uint8_t>& v);
		void half_word_write(uint32_t R_ADDR, uint32_t DATA, std::vector<uint8_t>& v);

		std::uint32_t word_read(uint32_t RADDR, const std::vector<uint8_t>& v);
		void word_write(uint32_t R_ADDR, uint32_t DATA, std::vector<uint8_t>& v);


	public:
		Memory();

		std::uint32_t read(uint32_t ADDR, char mode = 0);
		void write(uint32_t ADDR, uint32_t DATA, char mode = 0);
	
		std::uint32_t read_inst(uint32_t ADDR);
		void write_inst(uint32_t ADDR, uint8_t DATA);
		

		
		

	
};

#endif


//empty adddress - > exception
