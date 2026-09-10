#include<lpc21xx.h>
void UART_INIT(void)
{
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
void UART_TX(unsigned char tx)
{
	while(((U0LSR>>5)&1)==0);
		U0THR=tx;
}
unsigned char UART_RX(void)
{
	while((U0LSR&1)==0);
		return U0RBR;
}
void UART_STRING(unsigned char *s)
{
	while(*s)
	{
		UART_TX(*s++);
	}
}
