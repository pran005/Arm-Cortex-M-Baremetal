/**
  ******************************************************************************
  * @file    UART.h
  * @author  Pranjal Shrivastava
  * @version v2.0 - Cortex-M Faults  
  * @date    28-September-2020
  * @brief   Debug print header files   
  ******************************************************************************
 **/
#ifndef _UART_H
#define _UART_H

#include <stdint.h>

/** COLOUR DEFINITIONS **/  

#define ESC 			"\033"
#define ESC_RESET "\033[00m"
#define bRED 	   "[1;31;40m"
#define bGREEN   "[1;32;40m"
#define bCYAN 	 "[1;36;40m"


/*
 * @Brief : Initializes Debug UART on Tiva C Eval Kit 
 * @Parameters: None 
 * @Retval: None
 *
 */

void init_UART0(void) ; 

/*
 * @Brief : Transmits a single character over Debug UART
 * @Parameters: Char to be transmitted
 * @Retval: None
 *
 */

void UART0_Tx_c(char c) ; 

/*
 * @Brief : Converts a number to a hex string and transmits it over Debug UART
 * @Parameters: Number to be transmitted 
 * @Retval: None
 *
 */

void UART0_Tx_hex(uint32_t m) ;

/*
 * @Brief : Transmits a string over Debug UART 
 * @Parameters: Pointer to the string to be Transmitted 
 * @Retval: None
 *
 */

void UART0_Tx_s(char * string);

#endif
