
; Define address
; Same: #define RAM1_ADD 0x200000020
RAM1_ADD EQU 0x20000020 
RAM2_ADD EQU 0x20000030

; Start code 
	AREA Start, CODE, READONLY
	ENTRY
	EXPORT __main
			
			
			
			
__main
	LDR R0,=1 ; load 1 to R0
	LDR R1,=2
	ADD R2,R1,R0 ; R2= R1 + R0
	
	BL __FUNC1  ; jump to __FUNC1 then return
	
	B __FUNC2   ; jump to __FUNC2 not return
	

__FUNC1
	LDR R0,=6
	
	MOV PC,R14  ; move R14 to PC
	
	
__FUNC2
	LDR R0,=6
	
	;IF FUNCTION
	CMP R0, #8
	MOV R0, #8
	CMP R0, #8
	MOV R3, #0
	BEQ __LOOP     ; Branch equal
	
	
	
__LOOP
	; LOOP FUNCTION
	
	CMP R3, #10
	BEQ __WRITE
	; DO SOMETHING
	ADD R3, #1
	B __LOOP
	
	
__WRITE
	; WRITE TO SRAM
	LDR R0,=3;
	LDR R1,= RAM1_ADD
	LDR R2,= 0xABCDEF12
	
	
__LOOP_WRITE
	STR R2,[R1]
	ADD R1,R1,#4
	SUBS R0,R0,#1     ; "s" uptade flags
	BNE __LOOP_WRITE
	B __COPY
	
__COPY
	LDR R0,=3
	LDR R1,= RAM1_ADD
	LDR R2,= RAM2_ADD
	B __LOOP_COPY
	
__LOOP_COPY
	LDR R3,[R1]
	STR R3,[R2]
	ADD R1,R1,#4
	ADD R2,R2,#4
	SUBS R0,R0,#1
	BNE __LOOP_COPY
	
	
; shift variables: LSL, LSR
__SHIFT_FUNC
	LDR R0,=1
	LSL R1,R0,#1
	LSL R1,R1,#1

	
	

STOP B STOP
	END