/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
#include "Instruction.h"

// [REVIEW] ANDI works; just added comments

void andi_immd_assm(void) {

	// [ADD] Checking that the op code matches (previously had no comment)
	// [ADD] strcmp(string1, string2) return 0 if they match (previously had no comment)
	if (strcmp(OP_CODE, "ANDI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		[ADD] Checking the type of parameters (previously had no comment)
	*/

	// [ADD] param 1 should be a register (previously had no comment)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// [ADD] param 2 should be a register (previously had no comment)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// [ADD] param 3 should be an immediate (previously had no comment)
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		[ADD] Checking the value of parameters (previously had no comment)
	*/

	// [ADD] Rt should be 31 or less (previously had no comment)
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// [ADD] Rs should be 31 or less (previously had no comment)
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// [ADD] immediate is limited to 16 bits or 0xFFFF (previously had no comment)
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}


	/*
		[ADD] Combine Binary (previously had no comment)
	*/

	setBits_str(31, "001100"); 			// [ADD] Set the opcode (previously had no comment)
	setBits_num(20, PARAM1.value, 5);	// [ADD] Set Rt (previously had no comment)
	setBits_num(25, PARAM2.value, 5);	// [ADD] Set Rs (previously had no comment)
	setBits_num(15, PARAM3.value, 16);	// [ADD] Set immediate (previously had no comment)

	/*
		[ADD] Tell the system the encoding is done (previously had no comment)
	*/
	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	// [ADD] Check if the opcode bits match (previously had no comment)
	if (checkBits(31, "001100") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// get binary values
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	// set op
	setOp("ANDI");
	setParam(1, REGISTER, Rt); 
	setParam(2, REGISTER, Rs); 
	setParam(3, IMMEDIATE, imm16);
	
	// [ADD] tell the system the encoding is done (previously had no comment)
	state = COMPLETE_DECODE;
}



