#include "header.h"
#define sw1 ((IOPIN0>>14)&1)
#define sw2 ((IOPIN0>>15)&1)
extern u8 dtoh(u8);
extern void sec(void);
extern void min(void);
extern void hr_12_24(void);
extern void am_pm(void);
extern void mode_24(void);
extern void mode_12(void);
extern void year(void);
extern void mon(void);
extern void date(void);
extern void dow(void);
extern u8 isitleapyr(u8 yr);
extern u8 dayin_month(u8 yr,u8 month);
extern void lcd_info(u8 data);
