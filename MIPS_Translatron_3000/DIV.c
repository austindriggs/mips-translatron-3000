/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void div_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "DIV") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// param 1 should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// param 2 should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	setBits_str(31, "000000");
	setBits_num(20, PARAM1.value, 5);
	setBits_num(25, PARAM2.value, 5);
	setBits_str(5, "011010");
	setBits_num(15, 0, 10);
	
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// find binary
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("DIV");
	setParam(2, REGISTER, Rs);
	setParam(1, REGISTER, Rt);

	state = COMPLETE_DECODE;
}


