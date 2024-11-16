#include"header.h"
#define SI ((I2CONSET>>3)&1)
#define start (1<<5)
void i2c_init(void)
{
	PINSEL0|=0x50;
	I2SCLL=75;
	I2SCLH=75;
	I2CONSET=1<<6;
}

void i2c_byte_write(u8 sa,u8 mr,u8 data)
{
	// stp1:generate start condition
	I2CONSET=start;
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=start;
	if(I2STAT!=0x08)
	{
		uart0_tx_string("ERR: start fail \n\r");
		goto exit;
	}
	// stp2 send SA+W
	if(send_data(sa,0x20))
	{ 
		uart0_tx_string("ERR: SA+W fail \n\r");
		goto exit;
	} 
	// stp3 send mr addr 
	if(send_data(mr,0x30))
	{ 
		uart0_tx_string("ERR: mr addr fail \n\r");
		goto exit;
	}
	// stp4 send data
	if(send_data(data,0x30))
	{ 
		uart0_tx_string("ERR: data fail \n\r");
		goto exit;
	} 
	// stp5 generate stop cindition
	exit:
	I2CONCLR=(1<<3);
	I2CONSET=(1<<4);
}

u8 i2c_byte_read(u8 sa,u8 mr)
{
	u8 temp;
	// stp1:generate start condition
	I2CONSET=start;
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=start;
	if(I2STAT!=0x08)
	{
		uart0_tx_string("ERR: start fail \n\r");
		goto exit;
	}
	// stp2 send SA+W 
	if(send_data(sa,0x20))
	{ 
		uart0_tx_string("ERR: SA+W fail \n\r");
		goto exit;
	}
	// stp3 send mr addr
	if(send_data(mr,0x30))
	{ 
		uart0_tx_string("ERR: mr addr fail \n\r");
		goto exit;
	}
	// stp4: generate Restart condition
	I2CONSET=start;
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=start;
	if(I2STAT!=0x10)
	{
		uart0_tx_string("ERR: Restart fail \n\r");
		goto exit;
	}
	// stp5 send SA+R
	if(send_data(sa|1,0x48))
	{ 
		uart0_tx_string("ERR: SA+R fail \n\r");
		goto exit;
	} 
	// stp6 read data
	I2CONCLR=(1<<3);
	while(SI==0);
	temp=I2DAT;
	// stp7 generate stop cindition
	exit:
	I2CONSET=(1<<4);
	I2CONCLR=(1<<3);
	return temp;			
}


u8 send_data(u8 n,u8 code)
{
	I2DAT=n;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==code)
		return 1;
	else
		return 0;
}




