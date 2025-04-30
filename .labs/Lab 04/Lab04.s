		AREA My_Data, DATA, READWRITE
			
RES		DCD 0

		AREA My_Code, CODE, READONLY 
			
		ENTRY 
	
		EXPORT	__main
__main 
	
	MOV R0, #5  ; R0 = x
	MOV R1, #2  ; R1 = y
	MOV R2, #1  ; Counter
	MOV R3, R0 ; R3 = R0, used for each power
LOOP  
	CMPS R2, R1  ; Comparing the counter  to y
	BEQ SKIP     ; Exit Condition for Loop
	MUL R0, R0, R3 ; R0 * R0	
	ADD R2, R2, #1  ; Increment counter
	B LOOP			; Back to Loop

SKIP 		; End of Loop
	
	MOV R4, R0  ; Preserving x into R4
	BL func     ; Calling subroutine
	LDR R5, =RES  ; Setting Allocation of memory for x
	STR R0, [R5]  ; Storing the function f into memory
	
STOP
	B STOP 

func PROC
	PUSH{LR} 
	MUL R0, R4, R4 ; x^2 
	ADD R0, R0, R4 ; x^2 + x
	SUB R0, R0, #1 ; x^2 + x - 1
	POP{LR} 
	BX LR 
	ENDP ; end process
	NOP

	ALIGN
	END   ; end code