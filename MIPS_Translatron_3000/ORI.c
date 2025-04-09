/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// [REVIEW] ORI works and is fully implemented

#include "Instruction.h"

// Checking if the OPCODE is Ori 
void ori_immd_assm(void) {
	// Check if ORI
	if (strcmp(OP_CODE,"ORI") != 0){
		state = WRONG_COMMAND;
		return;
	}

	/* 
		Parameters 1 and 2 need to be a register while parameter 3 needs to be an immediate
	*/

	if (PARAM1.type != REGISTER){
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != REGISTER){
		state = MISSING_REG;
		return;
	}

	if (PARAM3.type != IMMEDIATE){
		state = INVALID_PARAM;
		return;
	}

	/*
		Check the values for each of the registers
	*/

	// Rt needs to be less than 31
	if (PARAM1.value > 31){
		state = INVALID_REG;
		return;
	}
	// Rs also needs to be less than 31
	if (PARAM2.value > 31){
		state = INVALID_REG;
		return;
	}

	// Immediate must be less than 0xFFFF
	if (PARAM3.value > 0xFFFF){
		state = INVALID_IMMED;
		return;
	}

	// Setting the opcode
	setBits_str(31, "001101");

	// Setting bits or Rt
	setBits_num(20, PARAM1.value, 5);

	// Settting bits for Rs
	setBits_num(25, PARAM2.value, 5);

	// Setting the immediate value
	setBits_num(15, PARAM3.value, 16);

	// Completing the encode 
	state = COMPLETE_ENCODE;
}

void ori_immd_bin(void) {

	//  Now we will check to see if the bits match. First, the opcode must match 001101 for ORI
	if (checkBits(31, "001101") != 0){
		state = WRONG_COMMAND;
		return;
	}

	// This gets the bits for the registers and immediates
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	// Set the opcode
	setOp("ORI");

	// Connecting the Parameters to their Register & immediate value
	setParam(1, REGISTER, Rt);
	setParam(2, REGISTER, Rs);
	setParam(3, IMMEDIATE, imm16);
	
	// Decode is complete
	state = COMPLETE_DECODE;
}