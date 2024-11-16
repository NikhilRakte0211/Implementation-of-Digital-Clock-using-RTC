#include"header.h"
extern u8 flag;
void Exnt0_ISR() __irq
{
	flag=1;
	EXTINT=1;
	VICVectAddr=0;
}

void config_vic_for_exnt0(void)
{
	VICIntSelect=0;
	VICVectCntl0=14|(1<<5);
	VICVectAddr0=(u32)Exnt0_ISR;
	VICIntEnable=1<<14;
}

void config_exnt0(void)
{
	PINSEL1|=1;
	EXTMODE=1;
	EXTPOLAR=0;	
}


