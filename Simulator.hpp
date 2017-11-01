/*
 * Simulator.hpp
 *
 *  Created on: Nov 1, 2017
 *      Author: kayne
 */

#ifndef SIMULATOR_HPP
#define	SIMULATOR_HPP

#define OPMASK 0xFC000000
#define S1MASK 0x03E00000
#define S2MASK 0x001F0000

#define RDMASK 0x0000F800
#define RSHMASK 0x000007C0
#define RFMASK 0x0000003F

#define IDMASK 0x0000FFFF

#define JAMASK 0x03FFFFFF


class Simulator{

private:
	/*Memory mem;
	Register reg;*/
	int Inst;
	int opcode;
	int instType ; // 0 For R, 1 for I , 2 for J

	int Rsource1;
	int	Rsource2;
	int Rdest;
	int Rshift;
	int RFunct;

	int Isource1;
	int Isource2;
	int Idata;

	int Jaddress;

	int ALUOp;
	bool RegDst;
	bool ALUSrc;
	bool MemtoReg;
	bool RegWrite;
	bool MemRead;
	bool MemWrite;
	bool Branch;
	bool PCSrc;
	bool jump;



public:
	Simulator();
	Simulator(int pc_in);
	void run();
	int pc;

	void setInstAndType(int binInst);
	void setFieldandFlag();


};


#endif
