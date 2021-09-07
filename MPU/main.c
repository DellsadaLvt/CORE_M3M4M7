#include "stm32f10x.h"                  // Device header



typedef struct{
	uint32_t TYPE;
	uint32_t CTRL;
	uint32_t RNR;
	uint32_t RBAR;
	uint32_t RASR;
}MPU_TypeDef;

#define MPU ((MPU_TypeDef*)0xE000ED90)


void MPU_Config( void );



int main( void ){
	*(uint32_t*)0x20000000= 3u;
	
	MPU_Config();
	*(uint32_t*)0x20000000= 5u;
	//*(uint32_t*)0x08000200= 5u;
	while(1){
		
	}
}

void MPU_Config( void ){
	MPU->RNR = 0; // MPU Region Number Register
	// select region 0
	MPU->RBAR = 0x00000000; // MPU Region Base Address Register
	// Base Address = 0x00000000
	MPU->RASR = 0x0607002F; // Region Attribute and Size Register
	// R/W, TEX=0,S=1,C=1,B=1, 16MB, Enable=1
	MPU->RNR = 1; // select region 1
	MPU->RBAR = 0x20000000; // Base Address = 0x20000000
	MPU->RASR = 0x0007002F; // R/W, TEX=0,S=1,C=1,B=1, 64MB, Enable=1
	MPU->RNR = 2; // select region 2
	MPU->RBAR = 0x40000000; // Base Address = 0x40000000
	MPU->RASR = 0x03050033; // R/W, TEX=0,S=1,C=0,B=1, 64MB, Enable=1
	MPU->RNR = 3; // select region 3
	MPU->RBAR = 0xA0000000; // Base Address = 0xA0000000
	MPU->RASR = 0x01040027; // Privileged R/W, TEX=0,S=1,C=0,B=0,
	// 1MB, Enable=1
	MPU->CTRL = 1; // MPU Control register – Enable MPU
}
















