#include "stm32f10x.h"                  // Device header

void changePrivileges( void);

int main( void ){

	changePrivileges( );
	while(1){
		
	}
}



void changePrivileges( void){
	/* read value of control Register */
	__asm volatile ( "MRS R0,CONTROL" );
	/* modify */
	//__asm volatile ( "MOV R0,#1" );
	__asm volatile ( "ORR R0,R0,#1" );
	/* change to unprivilege */
	__asm volatile ( " MSR CONTROL,R0 " );
	
	
	//__asm volatile ("MSR CONTROL,R0");
}

//void ChangeAccessLevelUnpriv(void)
//{
//	//read
//	__asm volatile ("MRS R0,CONTROL");
//	//modify
//	__asm volatile ("ORR R0,R0,#0x01");
//	//write
//	__asm volatile ("MSR CONTROL,R0");
//}







