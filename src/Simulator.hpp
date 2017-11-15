/*
 * Simulator.hpp
 *
 *  Created on: Nov 1, 2017
 *      Author: kayne
 */
#ifndef SIMULATOR_HPP
#define	SIMULATOR_HPP

#include "Memory.hpp"
#include "Register.hpp"
#include "Debug.hpp"
#include <cstdint>
#include <vector>


#define PC_INITIAL 0x10000000
#define ADDR_NULL 0x00000000

#define OP_MASK 0xFC000000

#define RS_MASK 0x03E00000
#define RT_MASK 0x001F0000
#define RD_MASK 0x0000F800
#define SHAMT_MASK 0x000007C0
#define FUNCT_MASK 0x0000003F

#define IM_MASK 0x0000FFFF
#define JA_MASK 0x03FFFFFF


class Simulator{

public:
	Simulator();
	std::uint32_t run();
	void load_bin(const std::vector<std::uint8_t>& v_byte_inst);
	


private:
	std::uint32_t (Simulator::*opcode_table[8][8])() = {
		{&Simulator::stub,&Simulator::conditional_B,&Simulator::j,&Simulator::jal,&Simulator::beq,&Simulator::bne,&Simulator::blez,&Simulator::bgtz},

		{&Simulator::addi,&Simulator::addiu,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::lb,&Simulator::lh,&Simulator::stub,&Simulator::lw,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::sb,&Simulator::sh,&Simulator::stub,&Simulator::sw,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub}};

	
	std::uint32_t (Simulator::*funct_table[8][8])()=  {
		{&Simulator::sll,&Simulator::stub,&Simulator::srl,&Simulator::sra,&Simulator::sllv,&Simulator::stub,&Simulator::srlv,&Simulator::srav},

		{&Simulator::jr,&Simulator::jalr,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::mfhi,&Simulator::mthi,&Simulator::mflo,&Simulator::mtlo,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::mult,&Simulator::multu,&Simulator::div,&Simulator::divu,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::add,&Simulator::addu,&Simulator::sub,&Simulator::subu,&Simulator::bwand,&Simulator::bwor,&Simulator::bwxor,&Simulator::bwnor},

		{&Simulator::stub,&Simulator::stub,&Simulator::slt,&Simulator::sltu,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub}};

	Memory mem;
	Register reg;
	std::uint32_t pc;
	std::uint32_t instruction;
	std::uint32_t r_operands[5];
	std::uint32_t i_operands[3];
	std::uint32_t j_operands[1];
	
	std::uint32_t branch_taken;
	std::uint32_t branch_address;

	void fetch_instruction();
	void decode();
	void update_pc();

	std::uint32_t sign_extend(std::int32_t a,int bits);


	std::uint32_t stub();
	std::uint32_t invalid_func();

	std::uint32_t conditional_B();
	std::uint32_t bltz();
	std::uint32_t bltzal();
	std::uint32_t bgezal();
	std::uint32_t bgez();
	std::uint32_t j();
	std::uint32_t jal();
	std::uint32_t beq();
	std::uint32_t bne();
	std::uint32_t blez();
	std::uint32_t bgtz();
	std::uint32_t addi();
	std::uint32_t addiu();
	std::uint32_t slti();
	std::uint32_t sltiu();
	std::uint32_t andi();
	std::uint32_t ori();
	std::uint32_t xori();
	std::uint32_t lui();
	std::uint32_t lb();
	std::uint32_t lh();
	std::uint32_t lwl();
	std::uint32_t lw();
	std::uint32_t lbu();
	std::uint32_t lhu();
	std::uint32_t lwr();
	std::uint32_t sb();
	std::uint32_t sh();
	std::uint32_t swl();
	std::uint32_t sw();
	std::uint32_t swr();
	
	//R-type Inst:
	std::uint32_t sll();
	std::uint32_t srl();
	std::uint32_t sra();
	std::uint32_t sllv();
	std::uint32_t srlv();
	std::uint32_t srav();
	std::uint32_t jr();
	std::uint32_t jalr();
	std::uint32_t mfhi();
	std::uint32_t mthi();
	std::uint32_t mflo();
	std::uint32_t mtlo();
	std::uint32_t mult();
	std::uint32_t multu();
	std::uint32_t div();
	std::uint32_t divu();
	std::uint32_t add();
	std::uint32_t addu();
	std::uint32_t sub();
	std::uint32_t subu();
	std::uint32_t bwand();
	std::uint32_t bwor(); 
	std::uint32_t bwxor();
	std::uint32_t bwnor();
	std::uint32_t slt();
	std::uint32_t sltu();

};


#endif
