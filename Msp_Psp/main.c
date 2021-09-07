#include "stm32f10x.h"                  // Device header

void ConfigSysTick( void );
__asm void MSP2PSP( void );


int main( void ){
	MSP2PSP();
	ConfigSysTick();
	while(1){
	}
}




/*================= SOBROUTINE ===================== */

void ConfigSysTick( void ){
	SysTick->LOAD= 36000u - 1u;
	SysTick->VAL= 0u;
	SysTick->CTRL= 7u;
}


__asm void MSP2PSP( void ){
	LDR R0,=0x20000770
	MSR PSP,R0
	LDR R0,=2
	MSR CONTROL,R0
	BX LR
}

void SysTick_Handler( void ){

}











