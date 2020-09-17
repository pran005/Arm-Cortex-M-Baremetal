/**
  ******************************************************************************
  * @file    main.c 
  * @author  Pranjal Shrivastava
  * @version v1.5 - Cortex-M Faults  
  * @date    12-September-2020
  * @brief   Main program body 
  ******************************************************************************
 **/
 
#include  <tm4c123gh6pm.h>
#include  "faults.h" 

/** @TODO: 
												
  MemManage Faults:	1. DACCVIOL
			2. MSTKERR
			3. MUNSKERR
			4. MLSPERR 		 (Specific to FPU)
		
 Bus Fault : 				
			1. UNSTKERR
			2. LSPERR (Specific to FPU)
													
**/
	

uint8_t buffer[10] __attribute__((aligned(4)));
volatile void *gl_unaligned_buffer;

int main(void)
{
	gl_unaligned_buffer = &buffer[1];  //mis-align the buffer

	trigger_fault(BUS_FAULT_STKERR) ; 
	while(1) ; 
 
}
