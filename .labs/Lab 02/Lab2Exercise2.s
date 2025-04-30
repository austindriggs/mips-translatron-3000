		AREA My_Code, CODE, READONLY
	
		EXPORT  __main
__main

	MOV R1, #5   ; Set R1 equal to some value
	CMPS R1, #0   ; Compare R1 to 0
	BGE SET_MIN_5 ; If R1 is greater than zero, go to less than 5 test
	B SKIP
SET_MIN_5 SUBS R1, R1, #5  ; Used to see if R1 is negative when subtracting 5
	BMI SET_R1    ; Go to move statement if R1 is negative, when 5 is subtracted
	B SKIP
	
SET_R1 MOV R1, #10  ; R1 equals 10 when in the range of zero to 5

SKIP;

	NOP
	
	ALIGN
	END