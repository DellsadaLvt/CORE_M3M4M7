#include "stm32f10x.h"                  // Device header

uint32_t x, x2;
void Count1( void );
void Count2( void );
void ConfigSysTick( void );
	
int main( void ){
	uint8_t i= 1;
	ConfigSysTick();
	while(1){
		if( i )
			Count1();
		else
			Count2();
		
	}
}



void Count1( void ){
	
	while(1){
		x++;
		//HAL_Delay(1000u);
	}
}

void Count2( void ){
	while(1){
		x2++;
		//HAL_Delay(1000u);
	}
}

void ConfigSysTick( void ){
	SysTick->LOAD= 36000u - 1u;
	SysTick->VAL= 0u;
	SysTick->CTRL= 7u;
}


void SysTick_Handler( void ){


}





