#include "stm32f10x.h"                  // Device header

void SysTickConfig( void );  __attribute__((section(".RamFunc")));

int main( void ){
	SysTickConfig();
	while(1){
	}
}




void SysTickConfig( void ){
	SysTick->LOAD= 71999999u;
	SysTick->VAL= 0u;
	SysTick->CTRL= 7u;

}









