#include"rtcheader.h"
extern u8 h,yy,mm;

void dow(void)
{
	u8 day=1;
	lcd_cmd(0x1);
	lcd_string("DOW");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			day++;
			if(day==8)
			{
				lcd_cmd(0x1);
				lcd_string("DOW");
				day=1;
			}
		}	
		lcd_cmd(0xc0);
		switch(day)
		{
			case 1:lcd_string("SUN");break;
			case 2:lcd_string("MON");break;
			case 3:lcd_string("TUE");break;
			case 4:lcd_string("WED");break;
			case 5:lcd_string("THU");break;
			case 6:lcd_string("FRI");break;
			case 7:lcd_string("SAT");break;
		}
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	i2c_byte_write(0xd0,0x3,day);
}
///////////////////////////////////////////
void date(void)
{
	u8 m=1,n;
	lcd_cmd(0x1);
	lcd_string("Date");
	n=dayin_month(yy,mm);
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			m++;
			if(m==n+1)
			{
				lcd_cmd(0x1);
				lcd_string("Date");
				m=1;
			}
		}	
		lcd_cmd(0xc0);
		lcd_atoi(m);
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	m=dtoh(m);
	i2c_byte_write(0xd0,0x4,m);
}

//////////////////////////////////////////
void mon(void)
{
	u8 m=1;
	lcd_cmd(0x1);
	lcd_string("MONTH");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			m++;
			if(m==13)
			{
				lcd_cmd(0x1);
				lcd_string("MONTH");
				m=1;
			}
		}
		
		lcd_cmd(0xc0);
		lcd_atoi(m);
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	mm=m;
	m=dtoh(m);
	i2c_byte_write(0xd0,0x5,m);
}

/////////////////////////////////////////
u8 isitleapyr(u8 yr)
{
	u32 y=2000+yr;
	if((y%4==0 && y%100!=0)|| (y%400==0))
		return 1;
	else
		return 0;
}
/////////////////////////////////////////
u8 dayin_month(u8 yr,u8 month)
{
	  switch(month)
	  {
	  		case 1:case 3:case 5:case 7:case 8:case 10:case 12:  return 31;
			case 4:case 6:case 9:case 11:	return 30;
			case 2:if(isitleapyr(yr))
					return 29;
				   else
				   	return 28;
	  }
	  return 0;
}


/////////////////////////////////////////
void year(void)
{
	u8 t=0;
	lcd_cmd(0x1);
	lcd_string("Year");
	lcd_cmd(0xc0);
	lcd_atoi(20);
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			t++;
			if(t==99)
			{
				lcd_cmd(0x1);
				lcd_string("Year");
				lcd_cmd(0xc0);
				lcd_atoi(20);
				t=1;
			}
		}
		lcd_cmd(0xc2);
		if(t<10)
			lcd_data('0');
		lcd_atoi(t);
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	yy=t;
	t=dtoh(t);
	i2c_byte_write(0xd0,0x6,t);
}
////////////////////////////////////////
void mode_12(void)
{
	u8 t=1;
	lcd_cmd(0x1);
	lcd_string("Hr");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			t++;
			if(t==13)
			{
				lcd_cmd(0x1);
				lcd_string("Hr");
				t=1;
			}
		}
		
		lcd_cmd(0xc0);
		lcd_atoi(t);
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	t=dtoh(t);
	h=h|t;

	i2c_byte_write(0xd0,0x2,h);	
}
////////////////////////////////////////
void mode_24(void)
{
	u8 t=0;
	lcd_cmd(0x1);
	lcd_string("Hr");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			t++;
			if(t==24)
			{
				lcd_cmd(0x1);
				lcd_string("Hr");
				t=0;
			}
		}
		
		lcd_cmd(0xc0);
		lcd_atoi(t);
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	//h=0;
	t=dtoh(t);
	h=h|t;
	
	i2c_byte_write(0xd0,0x2,h);	
}


//////////////////////////////////////////
u8 dtoh(u8 n)
{
	u8 t=0;
	t=(n/10)<<4;
	t=t|(n%10);
	return t;	
}
//////////////////////////////////////////////
void am_pm(void)
{
	lcd_cmd(0x01);
	lcd_string("Zone");
	lcd_cmd(0xc0);
	if((h>>5)&1)
			lcd_string("PM");
		else
			lcd_string("AM");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			h=h^(1<<5);
		}
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
		lcd_cmd(0xc0);
		if((h>>5)&1)
			lcd_string("PM");
		else
			lcd_string("AM");
	}	
}
//////////////////////////////////////////////
void hr_12_24(void)
{
	//u8 r;
	h=0;
	lcd_cmd(0x01);
	lcd_string("Mode");
	//r=(h>>6)&1;
	while(1)
	{
		lcd_cmd(0xc0);
		if((h>>6)&1)
			lcd_string("12 hr mode");
		else
			lcd_string("24 hr mode");	
		if(sw1==0)
		{
			while(sw1==0);
			h=h^(1<<6);
		}
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
		//r=(h>>6)&1;
	}
}
////////////////////////////////////////////////////
void min(void)
{
	u8 m=0;
	lcd_cmd(0x80);
	lcd_cmd(0x1);
	lcd_string("MIN");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			m++;
			if(m==60)
			{
				lcd_cmd(0x1);
				lcd_string("MIN");
				m=0;
			}
		}
		
		lcd_cmd(0xc0);
		lcd_atoi(m);
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	m=dtoh(m);
	i2c_byte_write(0xd0,0x1,m);
}

/////////////////////////////////////////////////////
void sec(void)
{
	u8 s=0;
	lcd_cmd(0x80);
	lcd_cmd(0x1);
	lcd_string("SEC");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			s++;
			if(s==60)
			{
				lcd_cmd(0x1);
				lcd_string("SEC");
				s=0;
			}
		}
		
		lcd_cmd(0xc0);
		lcd_atoi(s);
		if(sw2==0)
		{
			while(sw2==0);
			break;
		}
	}
	s=dtoh(s);
	i2c_byte_write(0xd0,0x0,s);
}
/////////////////////////////////////////////////////
void lcd_info(u8 data)
{
	lcd_data((data/0x10)+48);
	lcd_data((data%0x10)+48);
}
////////////////////////////////////////////////////////




