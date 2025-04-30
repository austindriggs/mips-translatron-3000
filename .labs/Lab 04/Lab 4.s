		AREA My_Code, CODE, READONLY 
	
		EXPORT	__main
__main 
	
	MOV R0, #6  ; R0 = x
	MOV R1, #3  ; R1 = y
	MOV R2, #1  ; Counter
	MOV R3, R0 ; R3 = R0, used for each power
LOOP  
	CMPS R2, R3
	MUL R0, R0, R3 ; R0 * R0
	BEQ SKIP 
	ADD R2, R2, #1 
	B LOOP

SKIP 
	NOP

	ALIGN
	END 
