#include "stm32f10x.h"                  // Device header


#define TIME_DELAY 10000000


void delay( uint32_t u32TimeDelay );
void BlinkLed( void );

int main( void ){
	/* enable clk port C */
	RCC->APB2ENR|= 0x01 << 4u;
	/* Config PC13 as output */
	GPIOC->CRH &= 0xFF3FFFFF;
	GPIOC->CRH |= 0x00300000;
	while(1){
		BlinkLed();
	}
}


/* Delay function */
void delay( uint32_t u32TimeDelay ){
	/* loop wait a seconds */
	for( uint32_t i= u32TimeDelay; i> 0; i--){
	}
}

void BlinkLed( void ){
	__asm(
	"	MOV R6,#0x40011010   	\n"
	"	LDR R7,[R6] 					\n"
	"	ORR R7,R7,#0x00002000	\n"
	"	STR R7,[R6]						\n"
	);
	delay( TIME_DELAY);
	__asm(
	"	MOV R6,#0x40011010   	\n"
	"	LDR R7,[R6] 					\n"
	"	ORR R7,R7,#0x20000000	\n"
	"	STR R7,[R6]						\n"
	);
	delay( TIME_DELAY);
}









