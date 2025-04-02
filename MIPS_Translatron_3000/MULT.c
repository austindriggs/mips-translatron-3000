#include "Instruction.h"

// [ADD] Implemented whole file

void mult_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if(strcmp(OP_CODE, "MULT") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	
	/*
		Checking the type of parameters
	*/

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter should be a register
	if (PARAM3.type != REGISTER) {
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

	// Rt should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_num(31, 0, 6);

	// Set the function
	setBits_str(5, "011000");

	// set Rd
	setBits_num(15, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5); 

	// Set Rt
	setBits_num(20, PARAM3.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
	// If the opcode doesn't match, this isn't the correct command
	if(checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the opcode bits match, check the type of parameters

	/*
		Finding values in the binary
	*/

	// get Rt and Rs
	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	/*
		Setting instruction values
	*/

	//  Set the op code
	setOp("MULT");

	// Set the parameters
	setParam(1, REGISTER, Rd); //destination
	setParam(2, REGISTER, Rs); //first source register operand
	setParam(3, REGISTER, Rt); //second source register operand

	state = COMPLETE_DECODE;
}
