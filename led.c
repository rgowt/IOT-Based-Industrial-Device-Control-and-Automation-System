#include<lpc21xx.h>
#include<string.h>
#include "UART.h"
#include "lcd_display.h"
#define LED1 1<<14 
#define LED2 1<<15
#define LED3 1<<16
#define LED4 1<<17
void DELAY(int d)
{
	int i;
	for(;d>0;d--)
		for(i=12000;i>0;i--);
}
int main()
{
	unsigned char rx;
	UART_INIT();
	LCD_INIT();
	LCD_COMMAND(0x80);
	LCD_STRING("LED CONTROLLER");
	IODIR0|=LED1|LED2|LED3|LED4;
	IOSET0=LED1|LED2|LED3|LED4;
	
	while(1)
	{
		rx=UART_RX();
		//UART_TX=rx;
		if(rx=='1')
		{
			LCD_COMMAND(0xc0);
			IOCLR0=LED1;
			LCD_STRING("LED 1 ON.....");
				delay(1000);
		}
		else if(rx=='5')
		{
			LCD_COMMAND(0xc0);
			IOSET0=LED1;
			LCD_STRING("LED 1 OFF.....");
				delay(1000);
		}	
		else if(rx=='2')
		{
			LCD_COMMAND(0xc0);
			IOCLR0=LED2;
			LCD_STRING("LED 2 ON....");
				delay(1000);
		}
		else if(rx=='6')
		{
			LCD_COMMAND(0xc0);
			IOSET0=LED2;
			LCD_STRING("LED 2 OFF....");
				delay(1000);
		}
		else if(rx=='3')
		{
			LCD_COMMAND(0xc0);
			IOCLR0=LED3;
			LCD_STRING("LED3 ON.....");
				delay(1000);
		}
		else if(rx=='7')
		{
			LCD_COMMAND(0xc0);
			IOSET0=LED3;
			LCD_STRING("LED3 OFF.....");
				delay(1000);
		}
		else if(rx=='4')
		{
			LCD_COMMAND(0xc0);
			IOCLR0=LED4;
			LCD_STRING("LED4 ON.....");
				delay(1000);
		}
		else if(rx=='8')
		{
			LCD_COMMAND(0xc0);
			IOSET0=LED4;
			LCD_STRING("LED4 OFF.....");
			delay(1000);
		}
	
	}

}							    