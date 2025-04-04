# MIPS Translatron 3000

CPE310 Project - Spring 2025

## CONTRIBUTING

When contributing, add a comment in the form:
```c
// [WHAT] why (previous)
```

Where:
- The `[WHAT]` is what you did: CHANGE, ADD, REMOVE, or anything else. 
- The `why` is the reason for what you did. 
- The `previous` is a brief description of what was previously there just to keep a record for ourselves.

After changing files, you need to recompile:
```bash
gcc ADD.c ADDI.c AND.c ANDI.c BEQ.c BNE.c DIV.c LUI.c LW.c MFHI.c MFLO.c MIPS_Instruction.c MIPS_Interpreter.c MULT.c OR.c ORI.c SLT.c SLTI.c SUB.c SW.c -o MIPS_Interpreter.exe
```
