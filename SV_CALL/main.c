#include "stm32f10x.h"                  // Device header

volatile uint8_t u8IdFunc;


__asm void changeToUnprivileged( void );


int main ( void ){
	changeToUnprivileged();
	/* call SVC func 3 */
	__asm ("SVC #0x3");
	while(1){
	}
}



/*==================== SOUBROUNTINE =======================*/
void SysTickConfig( void ){
	SysTick->LOAD	= 72000000u - 1u;
	SysTick->VAL	= 0u;
	SysTick->CTRL	= 7u;
}



void SysTick_Handler( void ){
	
}



__asm void SVC_Handler( void ){
	IMPORT getIdSVcall
	IMPORT SysTickConfig
	IMPORT switchContex
	IMPORT u8IdFunc
	
	PRESERVE8 {TRUE}
	
	
	MRS R0,MSP
	PUSH {LR}
	BL getIdSVcall
	LDR R4,=u8IdFunc
	LDR R0,[R4,#0x00]
	BL switchContex
	POP {LR}
	BX LR
}




void getIdSVcall( uint32_t* u32pMspAddr){
	u8IdFunc= *(uint8_t *)(u32pMspAddr[6]- 2u);
}

void switchContex( uint8_t u8Mode ){
	switch( u8Mode ){
		case 1:
			break;
		case 3:
			SysTickConfig();
			break;
		default:
			break;
	}
}

__asm void changeToUnprivileged( void ){
	MRS R0,CONTROL
	ORR R0,R0,#1
	MSR CONTROL,R0
	BX LR
}

























