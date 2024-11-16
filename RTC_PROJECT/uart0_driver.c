#include"header.h"
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
void uart0_init(u32 baud)
{
	u32 result=0;
	s32 a[]={15,60,30,15,15};
	u32 pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	PINSEL0|=5;
	U0LCR=0x83;
	U0DLL=result&0xff;
	U0DLM=(result>>8)&0xff;
	U0LCR=3;
}
////////////////////////////////////////

void uart0_tx(u8 data)
{
	U0THR=data;
	while(THRE==0);
}
//////////////////////////////////////////
u8 uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

//////////////////////////////////////////////////
void uart0_tx_string(char *p)
{
	while(*p)
	{
		U0THR=*p;
		while(THRE==0);
		p++;
	}
}
///////////////////////////////////////////////////

void uart0_rx_string(char *s,int n)
{
int i;
	for(i=0;i<n;i++)
	{
		while(RDR==0);
		s[i]=U0RBR;
		if(s[i]=='\r')
			break;
	}
	s[i]='\0';
}

///////////////////////////////////////////////////

void uart0_tx_binary(u8 num)
{
	int pos;
	for(pos=7;pos>=0;pos--)
	{
		if((num>>pos)&1)
			uart0_tx('1');
		else
			uart0_tx('0');
	}
}
//////////////////////////////////////////////////////
void uart0_atoi(int n)
{
	int a[10],i;
	if(n==0)
		uart0_tx('0');
	if(n<0)
	{
		uart0_tx('-');
		n=-n;
	}
	i=0;
	while(n)
	{
		a[i]=n%10+48;
		n=n/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	uart0_tx(a[i]);
}
///////////////////////////////////////////////
void uart0_float(float f)
{
	int num;
	if(f==0)
	{
		uart0_tx_string("0.0");
		return;
	}
	if(f<0)
	{
		uart0_tx('-');
		f=-f;
	}
	num=f;
	uart0_atoi(num);
	uart0_tx('.');
	num=(f-num)*10;		                                                                                                                                                                          
	uart0_atoi(num);
}

////////////////////////////////////////










