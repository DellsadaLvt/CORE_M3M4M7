#include "stm32f10x.h"                  // Device header

char Func( char a, char b, char c, char d, char e);


int main( void ){
	Func(1,2,3,4, 5);
	while(1);
}




char Func( char a, char b, char c, char d , char e){
	return (a +b+c+d + e);
}






