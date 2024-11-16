#include"header.h"
void lcd_data(u8 data)
{
	u32 temp;
	IOCLR1=0xFE<<16;
	temp=(data&0xF0)<<16;
	IOSET1=temp;
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;

	IOCLR1=0xFE<<16;
	temp=(data&0x0F)<<20;
	IOSET1=temp;
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;
}
void lcd_cmd(u8 cmd)
{
	u32 temp;
	IOCLR1=0xFE<<16;
	temp=(cmd&0xF0)<<16;
	IOSET1=temp;
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;

	IOCLR1=0xFE<<16;
	temp=(cmd&0x0F)<<20;
	IOSET1=temp;
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;
}
void lcd_init(void)
{
	IODIR1=0xFE<<16;
	IOCLR1=1<<19;
	PINSEL2=0x0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
}
void lcd_string(s8 *p)
{
	while(*p)
	{
		lcd_data(*p);
		p++;
	}
}


void lcd_atoi(int n)
{
	int a[10],i;
	if(n==0)
		lcd_data('0');
	if(n<0)
	{
		lcd_data('-');
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
	lcd_data(a[i]);
}


void lcd_binary(u8 num)
{
	int pos;
	lcd_cmd(0x01);
	for(pos=7;pos>=0;pos--)
	{
		if((num>>pos)&1)
			lcd_data('1');
		else
			lcd_data('0');
	}
}

void lcd_float(float f)
{
int i;
	if(f==0)
	{
		lcd_string("0.000000");
		return;
	}
	if(f<0)
	{
		lcd_data('-');
		f=-f;
	}
	i=f;
	lcd_atoi(i);
	i=(f-i)*1000000;
	lcd_data('.');
	lcd_atoi(i);


}












