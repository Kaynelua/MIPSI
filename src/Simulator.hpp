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
	void (Simulator::*opcode_table[8][8])() = {
		{&Simulator::stub,&Simulator::conditional_B,&Simulator::j,&Simulator::jal,&Simulator::beq,&Simulator::bne,&Simulator::blez,&Simulator::bgtz},

		{&Simulator::addi,&Simulator::addiu,&Simulator::slti,&Simulator::sltiu,&Simulator::andi,&Simulator::ori,&Simulator::xori,&Simulator::lui},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::lb,&Simulator::lh,&Simulator::lwl,&Simulator::lw,&Simulator::lbu,&Simulator::lhu,&Simulator::lwr,&Simulator::stub},

		{&Simulator::sb,&Simulator::sh,&Simulator::stub,&Simulator::sw,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub},

		{&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub,&Simulator::stub}};

	
	void (Simulator::*funct_table[8][8])()=  {
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


	void stub();

	void conditional_B();
	void bltz();
	void bltzal();
	void bgezal();
	void bgez();
	void j();
	void jal();
	void beq();
	void bne();
	void blez();
	void bgtz();
	void addi();
	void addiu();
	void slti();
	void sltiu();
	void andi();
	void ori();
	void xori();
	void lui();
	void lb();
	void lh();
	void lwl();
	void lw();
	void lbu();
	void lhu();
	void lwr();
	void sb();
	void sh();
	void sw();
	
	//R-type Inst:
	void sll();
	void srl();
	void sra();
	void sllv();
	void srlv();
	void srav();
	void jr();
	void jalr();
	void mfhi();
	void mthi();
	void mflo();
	void mtlo();
	void mult();
	void multu();
	void div();
	void divu();
	void add();
	void addu();
	void sub();
	void subu();
	void bwand();
	void bwor(); 
	void bwxor();
	void bwnor();
	void slt();
	void sltu();

};


#endif
