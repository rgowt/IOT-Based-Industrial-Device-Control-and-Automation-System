#include<lpc21xx.h>
void UART_INIT(void);
void UART_TX(unsigned char):
unsgined char UART_RX(void);
void UART_STR(unsigned char *);
void UART_INIT(void)
{
	PINSEL0=0x5;
	U0CLR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0CLR=0x03;
}
void UART_TX(unsigned char tx);
{
	uOTHR=tx;
	while(((U0LSR>>5)&1)==0);
}
unsigned char UART_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void UART_STR(unsigned char *s)
{
	while(*s)
	{
		UART_TX(*s++);
	}
}


