/**
  ******************************************************************************
  * @file    faults.c 
  * @author  Pranjal Shrivastava
  * @version v1.5 - Cortex-M Faults  
  * @date    12-September-2020
  * @brief   Driver code for implementing faults 
  ******************************************************************************
 **/
 
#include "TM4C123.h"                    // Device header
#include  "faults.h" 

extern void *gl_unaligned_buffer;

void disable_n_access_fpu(void) 
{

  /* Let's disable the FPU */
  __asm volatile(
 
	     	  "ldr r0, =0xE000ED88 \n"
		  "mov r1, #0 \n"
		  "str r1, [r0]	\n"
		  "dsb \n"

		  /* Try to access FPU */
      		  "vmov r0, s0 \n"
     		 );
}

static void set_pending_irq(void) 
{
	
  NVIC->ISER[0] |= (1<<1) ;

  /* Pend an interrupt */ 
  NVIC->ISPR[0] |= (1<<1);
	
}

void bus_fault_stkerr(void) 
{
	
  uint8_t var;
  unsigned long long distance_from_ram_bottom = (uint32_t)&var - (uint32_t)0x20000000;
	
  /* Bloat up the RAM */ 
	
  volatile uint8_t buffer[distance_from_ram_bottom - 8];
	
  for (uint64_t i = 0; i < sizeof(buffer); i++) 
  {
    buffer[i] = i;
  }
  
  set_pending_irq();
}

void enable_qei_interrupts(void)
{
	/* The following sets up the QEI peripheral for the TM4C MCU */ 
	SYSCTL -> RCGCQEI |= (1<<0) ; 
	SYSCTL -> RCGCGPIO |= (1<<3) ;  

	GPIOD -> LOCK = 0x4C4F434B ; 
	GPIOD -> CR |= (1<<7) ; 
	GPIOD -> LOCK = 0x01 ; 
	GPIOD -> DEN |= (1<<7) | (1<<6) ; 
	GPIOD -> AFSEL |= (1<<6) | (1<<7) ; 
	GPIOD -> PCTL |= (1<<25)| (1<<26) | (1<<29) | (1<<30) ; 
		
	
	QEI0->MAXPOS = 0xFFFFFFFF ; 
	QEI0->LOAD = 25000000 ;	
	QEI0->CTL |= (1<<0) | (1<<3) | (1<<5) | (1<<13) ;
	QEI0->INTEN = (1<<1) ; 
	
	/* Enable Interrupt for QEI */
	NVIC_EnableIRQ(QEI0_IRQn) ; 
}


void bus_fault_precise(void)
{
	enter_unpriv_mode() ; 
	
	/* Accessing a "Privileged" register in unprivileged mode fires a bus fault - Joseph Yiu */ 

	NVIC_EnableIRQ(QEI0_IRQn) ;
	
	/** You can uncomment this and comment above 2 lines as well  **/ 
	/* 
	
	volatile uint32_t *a = (volatile uint32_t*)0x10000000 ;
	volatile uint32_t b = 12; 
	
	b = b/(*a) ;
	
	*/ 
}

void bus_fault_imprecise(void)
{
	 volatile uint64_t *buf = (volatile uint64_t *)0x30000000;
  	 *buf = 0x1122334455667788;
}

void bus_fault_ibuserr(void) 
{
	void (*fptr)(void) = (void(*)(void))0x00040000;		/* Bus Fault :  I-BUS Error */  	
	(*fptr)(); 

}

void mem_manage_iaccviol(void)
{
	void (*fptr)(void) = (void(*)(void))0xE0000615;	    /* MemManage fault : CPU tried to execute code from a eXecute Never memory region */																     // I-code fetch / Instruction Access violation  
	(*fptr)();

}

void usage_fault_invstate(void) 
{
	void (*fptr)(void) = (void(*)(void))0x00000514; /* usage fault: Invalid state due to T-Bit */ 
	(*fptr)();

}

void usage_fault_undefinstr(void) 
{
	void (*fptr)(void) = (void(*)(void))0x00001001;	 /* usage fault: Undefined instruction */
	(*fptr)();
}

void usage_fault_div_by_zero(void) 
{
	SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk ; 
	volatile uint32_t *a = (volatile uint32_t*)0xE000ED2A ;		/* The Reset value of UFSR(@0xE000ED2A) is 0x00 */ 
	volatile uint32_t b = 12; 

	b = b/(*a) ;  /* Attempt to divide by zero without the compiler knowing */ 

}

void usage_fault_invpc(void) 
{
	enable_qei_interrupts() ; 
}

void usage_fault_unaligned_mem_access(void)
{
	SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk ; 
	
	uint64_t *buf = gl_unaligned_buffer;
  	*buf = 0x1122334455667788;

}

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



void trigger_fault (fault_type_t fault_type)
{
	switch(fault_type) 
	{
		case BUS_FAULT_PRECISE:	bus_fault_precise(); 
		break ; 
		
		case BUS_FAULT_IMPRECISE: bus_fault_imprecise(); 
		break ; 

		case BUS_FAULT_IBUSERR: bus_fault_ibuserr(); 
		break ; 
		
		case MEM_MANAGE_IACCVIOL: mem_manage_iaccviol() ; 
		break ; 
		
		case USAGE_FAULT_INVSTATE: usage_fault_invstate() ; 
		break ;
	
		case USAGE_FAULT_UNDEFSTR: usage_fault_undefinstr() ; 
		break ;

		case USAGE_FAULT_INVPC: usage_fault_invpc() ; 
		break ; 		
		
		case USAGE_FAULT_DIV_BY_ZERO: usage_fault_div_by_zero() ; 
		break ; 
		
		case USAGE_FAULT_UNALIGNED_MEM_ACCESS: usage_fault_unaligned_mem_access() ; 
		break ; 
						
		case USAGE_FAULT_NOCP: disable_n_access_fpu() ; 
		break ; 
						
		case BUS_FAULT_STKERR: bus_fault_stkerr() ;  
	 	break ; 
						
	}

}
	
