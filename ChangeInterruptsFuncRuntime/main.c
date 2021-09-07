#include "stm32f10x.h"                  // Device header
#include <stdint.h>


#define VTOR_ADD 				((uint32_t*)0xE000ED08)


void SystickConfig( void );
void RegisterIQR( uint8_t u8Position, uint32_t* u32pFuncAdd );
void SyStick_IQR(  void );

int main( void ){
	*VTOR_ADD= 0x20000000;
	RegisterIQR(15u, (uint32_t*)SyStick_IQR);
	SystickConfig();
	while(1){
	}


}

void RegisterIQR( uint8_t u8Position, uint32_t* u32pFuncAdd ){
	*(uint32_t *)(*VTOR_ADD + u8Position*4u) = (uint32_t)u32pFuncAdd;
}


void SyStick_IQR(  void ){


}

void SystickConfig( void ){
	SysTick->VAL = 0u;
	SysTick->LOAD= 71999999u;
	SysTick->CTRL = 7u;
}


void SysTick_Handler (void ){

}





