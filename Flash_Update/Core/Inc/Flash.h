/*
 * Flash.h
 *
 *  Created on: Aug 21, 2021
 *      Author: LAPTOP
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "stm32f1xx.h"                  // Device header

typedef enum{
	success = 0,
	fault,
}check;


void earseFlash( uint32_t u32address );
check writeFlash( uint32_t u32Address, uint8_t* u8Buffer, uint32_t u32Length);
check readFlash( uint32_t u32AddressStart, uint8_t *u8Buffer, uint32_t u32Length);

#endif /* INC_FLASH_H_ */
