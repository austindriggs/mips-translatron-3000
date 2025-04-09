# Final Testing of MIPS Translatron 3000

This is just for reference:
```bash
Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> AND $t2, $t5, $t3
Hex: 0x01AB5024 Binary: 0000 0001 1010 1011 0101 0000 0010 0100 

Enter a line of assembly:
> 

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 1010 1011 0101 0000 0010 0100
AND $t2, $t5, $t3

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> ANDI $t6, $t3, #15
Hex: 0x316E000F Binary: 0011 0001 0110 1110 0000 0000 0000 1111

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0011 0001 0110 1110 0000 0000 0000 1111
ANDI $t6, $t3, #0xF

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> BEQ $t2, $t3, #15
Hex: 0x114B000F Binary: 0001 0001 0100 1011 0000 0000 0000 1111

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0001 0001 0100 1011 0000 0000 0000 1111
BEQ $t2, $t3, #0xF

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> BNE $t3, $t2, #10
Hex: 0x154B000A Binary: 0001 0101 0100 1011 0000 0000 0000 1010

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0001 0101 0100 1011 0000 0000 0000 1010
BNE $t3, $t2, #0xA

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 1

Enter Hex:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> DIV $t5, $t1
Hex: 0x01A9001A Binary: 0000 0001 1010 1001 0000 0000 0001 1010

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 1010 1001 0000 0000 0001 1010
DIV $t5, $t1


> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 1010 1001 0000 0000 0001 1010
DIV $t5, $t1

        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 1010 1001 0000 0000 0001 1010
DIV $t5, $t1


Enter Binary:
> 0000 0001 1010 1001 0000 0000 0001 1010
DIV $t5, $t1

DIV $t5, $t1


Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> LUI $t1, $t3, #2503
Hex: 0x3D6909C7 Binary: 0011 1101 0110 1001 0000 1001 1100 0111 

Enter a line of assembly:
> 

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0011 1101 0110 1001 0000 1001 1100 0111
LUI $t1, $t3, #0x9C7

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> MFHI $t5
Hex: 0x00006810 Binary: 0000 0000 0000 0000 0110 1000 0001 0000

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0000 0000 0000 0110 1000 0001 0000
MFHI $t5

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 1

Enter Hex:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> MFLO $t8
Hex: 0x0000C012 Binary: 0000 0000 0000 0000 1100 0000 0001 0010

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0000 0000 0000 1100 0000 0001 0010
MFLO $t8

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>  

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> MULT $t5, $t3
Hex: 0x01AB0018 Binary: 0000 0001 1010 1011 0000 0000 0001 1000

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 1010 1011 0000 0000 0001 1000
MULT $t5, $t3

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>  

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> OR $t5, $t6, $t7
Hex: 0x01CF6825 Binary: 0000 0001 1100 1111 0110 1000 0010 0101

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 1100 1111 0110 1000 0010 0101
OR $t5, $t6, $t7

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>  

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> ORI $t1, $zero, #15
Hex: 0x3409000F Binary: 0011 0100 0000 1001 0000 0000 0000 1111

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0011 0100 0000 1001 0000 0000 0000 1111
ORI $t1, $zero, #0xF

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> SLT $t1, $t2, $t3
Hex: 0x014B482A Binary: 0000 0001 0100 1011 0100 1000 0010 1010

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 0100 1011 0100 1000 0010 1010
SLT $t1, $t2, $t3

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> SLTI $t5, $t5, #5
Hex: 0x29AD0005 Binary: 0010 1001 1010 1101 0000 0000 0000 0101

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0010 1001 1010 1101 0000 0000 0000 0101
SLTI $t5, $t5, #0x5

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> SUB $t1, $t2, $t2 
Hex: 0x014A4822 Binary: 0000 0001 0100 1010 0100 1000 0010 0010

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code

>

Please enter an option:
        (1) Assembly to Machine Code

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 0000 0001 0100 1010 0100 1000 0010 0010
SUB $t1, $t2, $t2

Enter Binary:
> SW $t5, #9($t5)
ERROR: The given instruction was not recognized

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> SW $t5, #9($t5)
Hex: 0xADAD0009 Binary: 1010 1101 1010 1101 0000 0000 0000 1001

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 1010 1101 1010 1101 0000 0000 0000 1001
SW $t5, #0x9($t5)

Enter Binary:
>

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 1

Enter a line of assembly:
> LW $t6, #4($t5)
Hex: 0x8DAE0004 Binary: 1000 1101 1010 1110 0000 0000 0000 0100

Enter a line of assembly:
>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

>

Please enter an option:
        (1) Assembly to Machine Code
        (2) Machine Code to Assembly
        (3) Quit

> 2

Please select an option:
        (1) Hexadecimal to Assembly
        (2) Binary to Assembly
        [3] Main Menu

> 2

Enter Binary:
> 1000 1101 1010 1110 0000 0000 0000 0100
LW $t6, #0x4($t5)
```