#include "stm32f10x.h"                  // Device header

void SysTickInterruptConfig( void );
void Func_1( void );
void Func_2( void );


int main( void ){
	char thred= 1u;
	SysTickInterruptConfig();
	while(1){
		if(thred == 1u){
			Func_1();
		}else{
			Func_2();
		}
	}
}


/*===================== SUBROUTINE FUNC ====================*/
void SysTickInterruptConfig( void ){
	SysTick->VAL = 0u;
	SysTick->LOAD = 72000000u - 1u;
	SysTick->CTRL = 7u;
}


void SysTick_Handler( void ){
	Func_1();
	
}


void Func_1( void ){
	uint8_t count1= 0;
	while(1){
		count1++;
	}
}

void Func_2( void ){
	uint8_t count2= 0;
	while(1){
		count2++;
	}
}













