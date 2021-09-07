#include "Bitband.h"

#define u32BitbandBaseAddr   0x20000000
#define u32BitbandAliasAddr  0x2200000C

void Bitband_demo( void ){
	/* normal way */
	uint32_t *u32pValue;
	u32pValue= (uint32_t *)u32BitbandBaseAddr;
	*u32pValue = 0x11111111;
	
	/* use bitband */
	*(uint32_t*)u32BitbandAliasAddr= 1u;
	

}















