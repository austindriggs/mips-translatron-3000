	AREA	Variables, DATA, READWRITE
							; anything in this area is interpreted as data and stored as RAM
SUM		SPACE	4 			; allocates 4 bytes in RAM					
							

							
	AREA	My_Code, CODE, READONLY
NUM1	DCD		85
NUM2	DCD		170	
		
	ENTRY					; mark first instructions to execute
	
	EXPORT __main
__main
	LDR		R5, NUM1		; setup parameters
	LDR 	R6, NUM2
	MUL		R1, R5, R6		; r0 += r1
	LDR		R3, =SUM		; = gets pointer to address
	STR		R1, [R3]		; [brackets] dereferences pointer to R3
	
	NOP						; no operation
	
	END						; marks end of file