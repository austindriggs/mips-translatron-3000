/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
#include "Instruction.h"

void lui_immd_assm(void) {
	// Checking if the opcode is LUI
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Setting parameter types for PARAM1 & PARAM2 to Registers
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Setting parameter types for PARAM1 & PARAM2 to Registers
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Parameter 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	// Parameters one and two must not exceed 31 bits
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Parameters one and two must not exceed 31 bits
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The maximum immediate values for a 4-bit integer is FFFF
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// Setting the opcode
	setBits_str(31, "001111");

	// Setting Rt with bits and location
	setBits_num(20, PARAM1.value, 5);

	// Setting Rs with bits and location
	setBits_num(25, PARAM2.value, 5);

	// Setting immediate bits and location
	setBits_num(15, PARAM3.value, 16);

	// Encode is complete
	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	// Now we will see if the opcode matches. First, the first six bits must be 001111 for LUI
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Setting the bits and location in machine code for the registers and immediate
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	// Set the opcode
	setOp("LUI");

	// Connecting the parameters to their register values
	setParam(1, REGISTER, Rt); 
	setParam(2, REGISTER, Rs); 
	setParam(3, IMMEDIATE, imm16); 

	// Decode is complete
	state = COMPLETE_DECODE;
}
