#include "TM4C123.h"                    // Device header
#include  "faults.h" 

extern void *gl_unaligned_buffer;

void disable_n_access_fpu(void) 
{

  // Let's disable the FPU
  __asm volatile(
      "ldr r0, =0xE000ED88 \n"
      "mov r1, #0 \n"
      "str r1, [r0]	\n"
      "dsb \n"
      "vmov r0, s0 \n"
      );
}

static void set_pending_irq(void) 
{

	NVIC->ISER[0] |= (1<<1) ;

  // Pend an interrupt
  NVIC->ISPR[0] |= (1<<1);
	
  // flush pipeline to ensure exception takes effect before we return from this routine and the ISR doesn't fire before
  //__asm("isb");
}

void bus_fault_stkerr(void) {
	
  extern uint32_t _start_of_ram[];
  uint8_t var;
  unsigned long long distance_to_ram_bottom = (uint32_t)&var - (uint32_t)0x20000000;
	
	/* Bloat up the RAM */ 
	
  volatile uint8_t big_buf[distance_to_ram_bottom - 8];
	
  for (uint64_t i = 0; i < sizeof(big_buf); i++) {
    big_buf[i] = i;
  }
  
  set_pending_irq();
}

void enable_qei_interrupts(void)
{
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
	NVIC_EnableIRQ(QEI0_IRQn) ; 
}


void bus_fault_precise(void)
{
	enter_unpriv_mode() ; 
	
	/* Accessing a "Privileged" register in unprivileged mode fires a bus fault - Joseph Yiu */ 

	NVIC_EnableIRQ(QEI0_IRQn) ;
	
/** You can uncomment this and comment above 2 lines as well  **/ 
/** 
	
	volatile uint32_t *a = (volatile uint32_t*)0x10000000 ;
	volatile uint32_t b = 12; 
	
	b = b/(*a) ;
	
**/ 
}

void bus_fault_imprecise(void)
{
	 volatile uint64_t *buf = (volatile uint64_t *)0x30000000;
  *buf = 0x1122334455667788;
}

void bus_fault_ibuserr(void) 
{
	void (*fptr)(void) = (void(*)(void))0x00040000;		// Bus Fault :  I-BUS Error 
	
	(*fptr)(); 

}

void mem_manage_iaccviol(void)
{
	void (*fptr)(void) = (void(*)(void))0xE0000615;	    // MemManage fault : CPU tried to execute code from a eXecute Never memory region
																										 // I-code fetch / Instruction Access violation  
	(*fptr)();

}

void usage_fault_invstate(void) 
{
	void (*fptr)(void) = (void(*)(void))0x00000514; // usage fault: Invalid state due to T-Bit
	
	(*fptr)();

}

void usage_fault_undefinstr(void) 
{
	void (*fptr)(void) = (void(*)(void))0x00001001;	 // usage fault: Undefined instruction 
		
	(*fptr)();
}

void usage_fault_div_by_zero(void) 
{
	SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk ; 
	volatile uint32_t *a = (volatile uint32_t*)0xE000ED2A ;
	volatile uint32_t b = 12; 

	b = b/(*a) ;  

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
