#include"header.h"
void delay_sec(u32 sec)
{
	
	T1PC=0;
	T1PR=15000000-1;
	T1TC=0;
	T1TCR=1;
	while(T1TC<sec);
	T1TCR=0;
}

void delay_ms(u32 ms)
{
	T1PC=0;
	T1PR=15000-1;
	T1TC=0;
	T1TCR=1;
	while(T1TC<ms);							 
	T1TCR=0;
}
