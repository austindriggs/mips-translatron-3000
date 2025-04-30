	AREA	Variables, DATA, READWRITE
							; anything in this area is interpreted as data and stored as RAM
NUM1		DCD	0 			; allocates 4 bytes in RAM
NUM2		DCD 0			; allocates 4 bytes in RAM
RES			DCD 0
SUM 		DCD 0
	
	AREA	My_Code, CODE, READONLY

	ENTRY						; mark first instructions to execute

	EXPORT __main
__main	

	LDR R1, =NUM1 ; R1 pointer to NUM1
	LDR R2, =NUM2 ; R2 pointer to NUM2
	MOV R0, #5
	STR R0, [R1] ; NUM1 = 5
	MOV R0, #7
	STR R0, [R2] ; NUM2 = 7
	LDR R3, =RES ; R3 pointer to RES
	LDR R4, =SUM ; R4 pointer to SUM
	LDR R5, [R1] ; R5 = NUM1 = 5
	LDR R6, [R2] ; R6 = NUM2 = 7
	
	BL func ; branch to function
	
	STR R0, [R3] ; store R0 into RES
	STR R0, [R4] ; store R0 into SUM
	
STOP 
	B STOP ; infinite loop			
	
func PROC
	ADD R0, R5, R6 ; R0 = R5 + R6
	BX LR
	ENDP
	
	END							; marks end of file