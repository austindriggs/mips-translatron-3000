#include "Instruction.h"

void mult_reg_assm(void) {
    // Checking that the opcode matches
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

    // Set the opcode (R-type, so 000000)
    setBits_num(31, 0, 6);

    // Set Rs
    setBits_num(25, PARAM1.value, 5);

    // Set Rt
    setBits_num(20, PARAM2.value, 5);

    // Set function code (MULT = 011000)
    setBits_str(5, "011000");

    // Unused fields for Rd, shamt should be zero
    setBits_num(15, 0, 5);  // Rd field (not used)
    setBits_num(10, 0, 5);  // shamt (always zero)

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
    // If the opcode doesn't match, this isn't the correct command
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

    // Set the parameters (source registers)
    setParam(1, REGISTER, Rs);
    setParam(2, REGISTER, Rt);

    state = COMPLETE_DECODE;
}
