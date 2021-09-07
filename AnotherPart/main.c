#include "stm32f10x.h"                  // Device header
#include "Stacking.h"
#include "Stack.h"
#include "Bitband.h"

//extern uint32_t g_u32DataStore[8u];



int main( void ){
	//changeToPSP();
	//sysTickConfig(72000u);
	Bitband_demo();
	while(1){
	}
}


/*================== SUBROUTINE ===================*/
void SysTick_Handler( void ){
}
























