/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
#include "Instruction.h"

void lw_immd_assm(void) {
	// Checking if the opcode is LW
	if (strcmp(OP_CODE, "LW") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Setting parameter 1 to Register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Parameter 2 needs to be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_IMMED;
		return;
	}

	// Parameter 3 needs to be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// PARAM1 (Rt) must not exceed 31
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// PARAM3 (Rs) must not exceed 31
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// PARAM2 (offset) must be within 16-bit range
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// Setting the opcode
	setBits_str(31, "100011");

	// Setting Rt with bits and location
	setBits_num(20, PARAM1.value, 5);

	// Setting Rs with bits and location
	setBits_num(25, PARAM3.value, 5);

	// Setting immediate bits and location
	setBits_num(15, PARAM2.value, 16);

	// Encode is complete
	state = COMPLETE_ENCODE;
}

void lw_immd_bin(void) {
	// Now we will see if the opcode matches. First, the first six bits must be 100011 for LW
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Setting the bits and location in machine code for the registers and immediate
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	// Set the opcode
	setOp("LW");

	// Connecting the parameters to their register values
	setParam(1, REGISTER, Rt);
	setParam(3, REGISTER, Rs);
	setParam(2, IMMEDIATE, imm16);

	// Decode is complete
	state = COMPLETE_DECODE;
}
