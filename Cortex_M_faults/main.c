#include	<tm4c123gh6pm.h>
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
	
void QEI0_Handler(void)
{
	QEI0->ISC = (1<<1) ; 
	__asm("PUSH {R0}"); 
}


void enter_priv_mode(void)
{
	__asm ("MRS R1, CONTROL  \n"
	       "AND R1,R1, #0xFE \n"
				 "MSR CONTROL, R1  \n" ) ;
} 


void enter_unpriv_mode(void)
{
	__asm ("MRS R1, CONTROL") ; 
	__asm ("ORR R1,R1, #0x01") ;
	__asm ("MSR CONTROL, R1") ;
}



void trigger_fault (uint8_t fault_type)
{
	switch(fault_type) 
	{
		case 0:	bus_fault_precise(); 
						break ; 
		
		case 1: bus_fault_imprecise(); 
						break ; 

		case 2: bus_fault_ibuserr(); 
						break ; 
		
		case 3: mem_manage_iaccviol() ; 
						break ; 
		
		case 4: usage_fault_invstate() ; 
						break ;
		
		case 5: usage_fault_undefinstr() ; 
						break ;

		case 6: usage_fault_invpc() ; 
						break ; 		
		
		case 7: usage_fault_div_by_zero() ; 
						break ; 
		
		case 8: usage_fault_unaligned_mem_access() ; 
						break ; 
						
		case 9: disable_n_access_fpu() ; 
						break ; 
						
		case 10: bus_fault_stkerr() ;  
						 break ; 
						
	}

}
	
uint8_t buffer[10] __attribute__((aligned(4)));
volatile void *gl_unaligned_buffer;

int main(void)
{
	gl_unaligned_buffer = &buffer[1];  //mis-align the buffer

	trigger_fault(10) ; 
	while(1) ; 
 
}
