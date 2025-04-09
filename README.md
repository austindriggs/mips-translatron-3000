# MIPS Translatron 3000

CPE310 Project  
Spring 2025  


## CONTRIBUTING

### COMMENTING

When implementing a function, to the top of the file, add:
```c
/*
* Author: Ohm Squad
* Date: YYYY-MM-DD
* ByteForge Systems
* MIPS-Translatron 3000
*/
```

When contributing, if relevant, add a comment in the form:
```c
// [WHAT] why (previous)
```

Where:
- The `[WHAT]` is what you did: CHANGE, ADD, REMOVE, or anything else. 
- The `why` is the reason for what you did. 
- The `previous` is a brief description of what was previously there just to keep a record for ourselves.


### COMPILING

After changing files, you need to recompile:
```bash
gcc ADD.c ADDI.c AND.c ANDI.c BEQ.c BNE.c DIV.c LUI.c LW.c MFHI.c MFLO.c MIPS_Instruction.c MIPS_Interpreter.c MULT.c OR.c ORI.c SLT.c SLTI.c SUB.c SW.c -o MIPS_Interpreter.exe
```

Note that you need to be in the `./MIPS_Translatron_3000` directory when you run this or you will get `file does not exist` errors:
```bash
cd MIPS_Translatron_3000
```


### IMMEDIATES

When running immediate functions, use a `#`:
```arm-asm
ADDI $t0, $t1, #15
```

and when you convert back from binary to assembly it will give the immediate value as a hex number:
```arm-asm
ADDI $t0, $t1, #0xF
```


## REFERENCES

For some references and documentation, see the `docs` folder.

Note that the "MIPSzy instruction summary" from section 3.9 incorrectly states that MULT starts with `000100`, but it is actually `000000`, as it is a register type (r-type) opcode.


## CONTACTS

The Ohm Squad:
- Austin Driggs (ard00029@mix.wvu.edu)
- Nate Kirby (nwk00004@mix.wvu.edu)
- Tucker Wilson (trw00007@mix.wvu.edu)
- Ava Milano (avm00006@mix.wvu.edu)


## AI DISCLOSURE

AI was used when **generating comments only**, it was not used for code generation, corrections, formatting, or anything else.
