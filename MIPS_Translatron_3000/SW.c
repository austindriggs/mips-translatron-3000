/*
* Author: Ohm Squad
* Date: 2025-04-02
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Header Files
#include "Instruction.h"

void sw_immd_assm(void) {
    // Check the opcode for SW
    if (strcmp(OP_CODE, "SW") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    if (PARAM2.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    if (PARAM3.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    /*
        Checking the value of parameters
    */

    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    if (PARAM2.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    if (PARAM3.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Set the bits
    setBits_str(31, "101011");
    setBits_num(20, PARAM1.value, 5);
    setBits_num(15, PARAM2.value, 16);
    setBits_num(25, PARAM3.value, 5);

    // Tell the system the encode is complete
    state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
    // Check the opcode
    if (checkBits(31, "101011") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Set the register values
    uint32_t Rs = getBits(25, 5);      // base
    uint32_t Rt = getBits(20, 5);      // source
    uint32_t imm16 = getBits(15, 16);  // offset

    // Set the opcode
    setOp("SW");

    // MIPS format: SW rt, offset(rs) HAD to change the order and the immediate to get it to work.
    setParam(1, REGISTER, Rt);       // rt (value to store)
    setParam(2, IMMEDIATE, imm16);   // offset
    setParam(3, REGISTER, Rs);       // rs (base)

    state = COMPLETE_DECODE;
}