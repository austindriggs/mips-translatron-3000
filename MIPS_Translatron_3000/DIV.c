/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
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

    // Set the opcode
    setBits_str(31, "000000");

    // Set Rs
    setBits_num(25, PARAM1.value, 5);

    // Set Rt
    setBits_num(20, PARAM2.value, 5);

    // Set function code 
    setBits_str(5, "011010");

    // Unused fields should be zero
    setBits_num(15, 0, 5);
    setBits_num(10, 0, 5);
	
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
	setParam(1, REGISTER, Rs); // [CHANGE] Reordered parameters
	setParam(2, REGISTER, Rt);

	state = COMPLETE_DECODE;
}


