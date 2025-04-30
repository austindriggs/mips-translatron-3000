		AREA My_Code, CODE, READONLY
	
		EXPORT  __main
__main
	MVN   R0, #1
	ADDS  R0, R0, #2
	
	
	MOV   R0, #0x8000
	MOV   R1, #0x8000
	ANDS  R0, R0, R1
	
	
	MOV   R0, #3
	MOV   R1, #5
	SUBS  R0, R0, R1
	
	MOV   R0, #-10
	MOV   R1, #3
	SUBS  R0, R0, R1
	
	MOVT  R0, #0x7000
	MOVT  R1, #0x7000 
	ADDS  R0, R0, R1
	
	NOP
	
	ALIGN
	END
	