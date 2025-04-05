/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
#include "Instruction.h"

/*
    ASSEMBLY TO BINARY FUNCTION
*/

void mult_reg_assm(void) {
    // Checking that the opcode matches this function
    if (strcmp(OP_CODE, "MULT") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    // The first parameter should be a register (Rs)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The second parameter should be a register (Rt)
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    /*
        Checking the value of parameters
    */

    // Rs should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Rt should be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    /*
        Putting the binary together
    */

    // Set the opcode
    setBits_str(31, "000100");

    // Set Rs
    setBits_num(25, PARAM1.value, 5);

    // Set Rt
    setBits_num(20, PARAM2.value, 5);

    // Set function code
    setBits_str(5, "011000");

    // Unused fields should be zeroed out
    setBits_num(15, 0, 5);
    setBits_num(10, 0, 5);

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

/*
    BINARY TO ASSEMBLY FUNCTION
*/

void mult_reg_bin(void) {
    // If the opcodes don't match, this isn't the correct command
    if (checkBits(31, "000100") != 0 || checkBits(5, "011000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Extracting values from the binary
    */

    // Get Rs and Rt
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);

    /*
        Setting instruction values
    */

    // Set the opcode
    setOp("MULT");

    // Set the parameters / registers
    setParam(1, REGISTER, Rs);
    setParam(2, REGISTER, Rt);

    // Tell the system the encoding is done
    state = COMPLETE_DECODE;
}
