#include "Stack.h"

volatile uint32_t u32IsMsp= 10;

__asm void isMsp( void ){
	IMPORT u32IsMsp
	MOV R0, LR /* after into stick_function processor execute push{r4,rl} */
	LDR R1, =4
	AND R1,R0,R1
	CBZ R1, _verifyMsp
	LDR R0,=u32IsMsp
	STR R1,[R0]
	BX LR
	
	
_verifyMsp
	LDR R0,=u32IsMsp
	STR R1,[R0]
	BX LR
}


__asm void changeToPSP( void ){
	LDR R0,=0x20000A60
	MSR PSP,R0
	MRS R0,CONTROL
	ORR R0,R0,#2
	MSR CONTROL,R0
	BX LR
}
















