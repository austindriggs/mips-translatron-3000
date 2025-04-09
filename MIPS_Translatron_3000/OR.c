/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
#include "Instruction.h"

// [REVIEW] OR looks good already; needs more comments

void or_reg_assm(void) {
	// Checking if the opcode is OR
	if (strcmp(OP_CODE, "OR") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// First parameter must be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Second parameter must be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Third parameter must be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Validate register values (must be 0–31)
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Encoding: R-type format
	// Opcode field (bits 31–26) for R-type is always 000000
	setBits_num(31, 0, 6);

	// Function code for OR is 100101 (bits 5–0)
	setBits_str(5, "100101");

	// Destination register Rd is PARAM1 (bits 15–11)
	setBits_num(15, PARAM1.value, 5);

	// Source register Rs is PARAM2 (bits 25–21)
	setBits_num(25, PARAM2.value, 5);

	// Target register Rt is PARAM3 (bits 20–16)
	setBits_num(20, PARAM3.value, 5);

	// Encoding is complete
	state = COMPLETE_ENCODE;
}

void or_reg_bin(void) {
	// Check that opcode (bits 31–26) is 000000 and function code (bits 5–0) is 100101
	if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Extract register fields from machine code
	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	// Set the operation mnemonic
	setOp("OR");

	// Set the parameters (registers)
	setParam(1, REGISTER, Rd);
	setParam(2, REGISTER, Rs);
	setParam(3, REGISTER, Rt);

	// Decoding is complete
	state = COMPLETE_DECODE;
}
