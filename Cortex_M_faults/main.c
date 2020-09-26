/**
  ******************************************************************************
  * @file    main.c 
  * @author  Pranjal Shrivastava
  * @version v1.5 - Cortex-M Faults  
  * @date    12-September-2020
  * @brief   Main program body 
  ******************************************************************************
 **/
 
#include "TM4C123.h"                  
#include  "faults.h" 
#include  "UART.h"

/**
	@Note: In case of STKERR , no Debug prints will be observed, 
				 as the RAM usage will be 100% and thus no function call would be made
				 In case of a function call (resulting in another fault) inside the handler,
				 the CPU will go into a Lockup State. 

	@TODO: 
												
  MemManage Faults:	1. DACCVIOL
			2. MSTKERR
			3. MUNSKERR
			4. MLSPERR 		 (Specific to FPU)
		
  Bus Fault : 				
			1. UNSTKERR
			2. LSPERR 		 (Specific to FPU)
													
**/


uint8_t buffer[10] __attribute__((aligned(4)));
volatile void *gl_unaligned_buffer;

int main(void)
{
	
	init_UART0() ; 
	gl_unaligned_buffer = &buffer[1];  //mis-align the buffer
	trigger_fault(BUS_FAULT_PRECISE) ;
	while(1) ; 
 
}
