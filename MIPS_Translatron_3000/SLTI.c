/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
#include "Instruction.h"

void slti_immd_assm(void) {

	if (strcmp(OP_CODE, "SLTI") != 0){
		state = WRONG_COMMAND;
		return;
}
	if (PARAM1.type != REGISTER){
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != REGISTER){
		state = MISSING_REG;
		return;
	}

	if (PARAM3.type != IMMEDIATE){
		state = INVALID_IMMED;
		return;
	}

	if (PARAM1.value > 31){
		state = INVALID_REG;
		return;
	}

	if (PARAM2.value > 31){
		state = INVALID_REG;
		return;
	}

	if (PARAM3.value > 0xFFFF){
		state = INVALID_IMMED;
		return;
	}

	setBits_str(31, "001010");
	setBits_num(20, PARAM1.value, 5);
	setBits_num(25, PARAM2.value, 5);
	setBits_num(15, PARAM3.value, 16);

	state = COMPLETE_ENCODE;

}

void slti_immd_bin(void) {
	if (checkBits(31, "001010") != 0){
		state = WRONG_COMMAND;
		return; 
	}

	uint32_t Rs = getBits(25,5);
	uint32_t Rt = getBits(20,5);
	uint32_t imm16 = getBits(15, 16);

	setOp("SLTI");
	setParam(1, REGISTER, Rt);
	setParam(2, REGISTER, Rs);
	setParam(3, IMMEDIATE, imm16);
	state = COMPLETE_DECODE;
	
}