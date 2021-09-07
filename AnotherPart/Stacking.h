#ifndef _INC_STACKING_H_

#define _INC_STACKING_H_

#include "stm32f10x.h"                  // Device header

__asm void readStacking( void );
void copyData( uint32_t* u32pAddress );
void sysTickConfig( uint32_t tick );
__asm void storeLr( void );
__asm void getLr( void );



#endif /* _INC_STACKING_H_ */













