#include"rtcheader.h"
u8 h,yy,mm,flag=0;
main()
{
	u8 s,m,dd,day;
 	uart0_init(9600);
	i2c_init();
	lcd_init();
	config_vic_for_exnt0();
	config_exnt0();


//			sec();
//			min();
//			hr_12_24();
//			if((h>>6)&1)
//			{
//				am_pm();
//				mode_12();
//			}
//			else
//				mode_24();
//			year();
//			mon();
//			date();
//			dow();
//			lcd_cmd(0x01);

	while(1)
	{
		if(flag)
		{
			sec();
			min();
			hr_12_24();
			if((h>>6)&1)
			{
				am_pm();
				mode_12();
			}
			else
				mode_24();
			year();
			mon();
			date();
			dow();
			lcd_cmd(0x01);
		   flag=0;
		}  
		//////////////////////////////////////////////////////////////////////
			s=i2c_byte_read(0xd0,0x0);
			m=i2c_byte_read(0xd0,0x1);
			h=i2c_byte_read(0xd0,0x2);
			day=i2c_byte_read(0xd0,0x3);
			dd=i2c_byte_read(0xd0,0x4);
			mm=i2c_byte_read(0xd0,0x5);
			yy=i2c_byte_read(0xd0,0x6);

			if((h>>6)&1)
			{	
				lcd_cmd(0x8A);
				if((h>>5)&1)
					lcd_string("PM");
				else
					lcd_string("AM");
				h=h&0x1f;
			}
			//TIME
			lcd_cmd(0x80);
			lcd_info(h);
			lcd_data(':');
			lcd_info(m);
			lcd_data(':');
			lcd_info(s);
		   //DATE
			lcd_cmd(0xc0);
			lcd_info(dd);
			lcd_data('/');
			lcd_info(mm);
			lcd_data('/');
			lcd_atoi(20);
			lcd_info(yy);
			lcd_cmd(0xcb);
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
		

	}

}












