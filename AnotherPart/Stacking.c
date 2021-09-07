#include "Stacking.h"

uint32_t g_u32DataStore[8u];

__asm void readStacking( void ){
	IMPORT copyData
	/* Align value into stack */
	PRESERVE8 {TRUE}
	
	/* store MSP to R0 as the paremeter of copyData func */
	MRS R0,MSP
	/* save LR in to stack */
	PUSH {LR}
	BL copyData
	POP {LR}
	BX LR
}


/* The stacking is begin from the arr[2], arr[0] and arr[1] is the value of R4, LR */
void copyData( uint32_t* u32pAddress ){
	for( uint8_t count=0; count<10u; count++){
		g_u32DataStore[count]= *u32pAddress;
		u32pAddress++;
	}
}

void sysTickConfig( uint32_t tick ){
	/* disable systick */
	SysTick->CTRL = 0;
	/* init the RELOAD value */
	SysTick->LOAD = tick -1u;
	/* set priority  */
	//NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
	/* reset current counter */
	SysTick->VAL = 0;
	/* select clock */
	SysTick->CTRL |= 0x04;
	/* enable systick interrupts */
	SysTick->CTRL |= 0x02;
	/* enable systick */
	SysTick->CTRL |= 0x01;
}


__asm void storeLr( void ){
	PRESERVE8 {TRUE}
	PUSH {LR}
}



__asm void getLr( void ){
	PRESERVE8 {TRUE}
	POP {LR}
	BX LR
}










