/**
  ******************************************************************************
  * @file    UART.h
  * @author  Pranjal Shrivastava
  * @version v2.0 - Cortex-M Faults  
  * @date    28-September-2020
  * @brief   Debug print drivers  
  ******************************************************************************
 **/
 
#include "TM4C123.h"                    // Device header
#include  "UART.h"
#include <string.h>

void init_UART0(void)
{
	SYSCTL->RCGCUART |= (1<<0);                     // Enable the UART0 and UART1 module using the RCGCUART register
	SYSCTL->RCGCGPIO |= (1<<0);                    // Enables the Port A and Port B GPIO via the RCGCGPIO register  
  
	GPIOA->AFSEL |= (1<<1)|(1<<0);                // enables the alternate function on pin PA0 & PA1

	GPIOA->PCTL |= (1<<0)|(1<<4);               // Configure the GPIOPCTL register to select UART0 in PA0 and PA1
       	GPIOA->DEN |= (1<<0)|(1<<1);               // Enable the digital functionality in PA0 and PA1   

	UART0->CTL &= ~(1<<0);                                   // Disable UART0 by clearing UARTEN bit in the UARTCTL register
  
	UART0->IBRD = 325;                                     // Write the integer portion of the BRD to the UARTIRD register	
	UART0->FBRD = 33;                                     // Write the fractional portion of the BRD to the UARTFBRD register
	UART0->LCRH = (0x3<<5);                              // 8-bit, no parity, 1 stop bit  
  
	UART0->CC = 0x0;                                       // Configure the UART clock source as system clock
	UART0->CTL = (1<<0)|(1<<8)|(1<<9);                    // UART0 Enable, Transmit Enable, Recieve Enable
 
}


void UART0_Tx_c(char c)                                                    // function to print user's input.
{ 
  while((UART0->FR &(1<<5)) != 0);                                       // waits the program till the previous transmission was completed
  UART0->DR =c;                                                         // value of UART0 DATA REGISTER is equal to c
}

void UART0_Tx_hex(uint32_t m)  
{
	const uint8_t hex[] = "0123456789abcdef" ; 	
	char hex_string[10] ; 
	hex_string[0] = '0' ; 
	hex_string[1] = 'x' ; 
	
	for(int i=0; i<8; i++)
	{
		hex_string[9-i] = hex[((m>>4*i)&0x0F)] ; 
	}
	UART0_Tx_s(hex_string) ; 
	
}


void UART0_Tx_s(char * string)                                         // function to print a predefined string
{
  while(*string)
  {
    UART0_Tx_c(*(string++));                                           // printChar is called with every increment in string pointer
  }
}

