// library functions
#include<LPC21XX.H>
#include<string.h>


// datatype shortcuts
typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;

// delay functions
extern void delay_sec(u32);
extern void delay_ms(u32);

//lcd 8 bit driver
extern void lcd_cmd(u8);
extern void lcd_data(u8);
extern void lcd_init(void);
extern void lcd_string(s8 *);
extern void lcd_atoi(int );
extern void lcd_binary(u8);
extern void lcd_float(float );


//uart driver
extern void uart0_init(u32);
extern void uart0_tx(u8);
extern u8 uart0_rx(void);
extern void uart0_tx_string(char *p);
extern void uart0_rx_string(char *s,int n);
extern void uart0_tx_binary(u8);
extern void uart0_atoi(int n);
extern void uart0_float(float f);

//adc driver 
extern u32 adc_read(u8 channel_num);
extern void adc_init(void);

//spi driver
extern void spi_init(void);
extern u8 spi_read(u8);
extern u32 mcp3204(u8 ch_num);


//uart0 intrupt
extern void config_vic_for_uart0(void);
extern void config_uart0(void);

//timer interupt
extern void config_timer0(u32);
extern void config_vic_timer0(void);

//Exnt interupt
extern void config_exnt0(void);
extern void config_vic_for_exnt0(void);

//i2c driver
extern void i2c_init(void);
extern void i2c_byte_write(u8 sa,u8 mr,u8 data);
extern u8 i2c_byte_read(u8 sa,u8 mr);
//I2C DRIVER mine
extern u8 send_data(u8 n,u8 code);
//extern void I2C_byt_wrt(u8 sa,u8 mr,u8 data);
//extern u8 I2C_byt_read(u8 sa,u8 mr);





