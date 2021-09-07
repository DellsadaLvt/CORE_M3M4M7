/*
 * Privileged.c
 *
 *  Created on: Aug 22, 2021
 *      Author: LAPTOP
 */

#include "Privileged.h"

void changeToUnprivileged( void ){
	//read
	__asm volatile ("MRS R0,CONTROL");
	//modify
	__asm volatile ("ORR R0,R0,#0x01");
	//write
	__asm volatile ("MSR CONTROL,R0");
}


void changeToPrivileged( void ){
	/* read value of control register into R0 */
	__asm volatile ("MRS R0,CONTROL");
	/* modify */
	__asm volatile ("AND R0,R0,#0x02");
	/* change to unprivileged mode */
	__asm volatile ("MSR CONTROL,R0");
}











