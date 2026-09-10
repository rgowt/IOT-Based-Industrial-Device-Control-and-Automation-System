#include<lpc21xx.h>
#define LCD 0xff<<4
#define RS 1<<12
#define E 1<<13
void delay(int d)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<d);
	T0TCR=0x03;
	T0TCR=0x00;
}

void LCD_COMMAND(unsigned char cmd)
{
	IOCLR0=LCD;
	IOSET0=cmd<<4;
	IOCLR0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
 void LCD_INIT(void)
{
	IODIR0|=LCD|RS|E;
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x02);
	LCD_COMMAND(0x0c);
	LCD_COMMAND(0x38);
}
void LCD_DATA(unsigned char d)
{
	IOCLR0=LCD;
	IOSET0=d<<4;
	IOSET0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
void LCD_STRING(unsigned char *s)
{
	while(*s)
	{
		LCD_DATA(*s++);
	}
}