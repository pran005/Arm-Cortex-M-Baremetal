#include <stdint.h>

typedef enum
{
	
	BUS_FAULT_PRECISE = 0,
	BUS_FAULT_IMPRECISE,
	BUS_FAULT_IBUSERR,
	MEM_MANAGE_IACCVIOL,
	USAGE_FAULT_INVSTATE,
        USAGE_FAULT_UNDEFSTR,
	USAGE_FAULT_INVPC,
	USAGE_FAULT_DIV_BY_ZERO,
	USAGE_FAULT_UNALIGNED_MEM_ACCESS,
	USAGE_FAULT_NOCP,
	BUS_FAULT_STKERR,
	
} FAULT_TYPE;

/*
 * @Brief : Disables the FPU 
 * @Parameters: None 
 * @Retval: None
 *
 */

void disable_n_access_fpu(void) ; 

/*
 * @Brief : Switches to unprivileged level execution   
 * @Parameters: None 
 * @Retval: None
 *

*/
void enter_unpriv_mode(void) ; 

/*
 * @Brief : Switches to privileged level execution 
 * @Parameters: None 
 * @Retval: None
 *
 */

void enter_priv_mode(void) ; 

/*
 * @Brief : Enables QEI peripherral in interrupt mode
 * @Parameters: None 
 * @Retval: None
 *
 */

void enable_qei_interrupts(void) ; 

/*
 * @Brief : Generates Precise Bus Fault
 * @Parameters: None 
 * @Retval: None
 *
 */

void bus_fault_precise(void); 

/*
 * @Brief : Generates Imprecise Bus Fault
 * @Parameters: None 
 * @Retval: None
 *
 */

void bus_fault_imprecise(void) ;

/*
 * @Brief : Generates instruction Bus Fault
 * @Parameters: None 
 * @Retval: None
 *
 */

void bus_fault_ibuserr(void) ; 

/*
 * @Brief : Generates I-code bus access MemManage fault
 * @Parameters: None 
 * @Retval: None
 *
 */

void mem_manage_iaccviol(void);

/*
 * @Brief : Forces the CPU to invalid state by resetting the 'T' Bit of EPSR causing Usage Fault 
 * @Parameters: None 
 * @Retval: None
 *
 */

void usage_fault_invstate(void) ;

/*
 * @Brief : Forces the CPU to execute an undefined instruction causing Usage Fault
 * @Parameters: None 
 * @Retval: None
 *
 */

void usage_fault_undefinstr(void) ; 

/*
 * @Brief : Enables the div by zero fault and forces the CPU to divide by zero  
 * @Parameters: None 
 * @Retval: None
 *
 */

void usage_fault_div_by_zero(void)  ; 

/*
 * @Brief : Forces the CPU to load an invalid value of PC by messing up the stack  
 * @Parameters: None 
 * @Retval: None
 *
 */

void usage_fault_invpc(void) ; 

/*
 * @Brief : Enables unaligned fault and attempts to read from an unaligned memory location  
 * @Parameters: None 
 * @Retval: None
 *
 */

void usage_fault_unaligned_mem_access(void) ; 

/*
 * @Brief : Triggers relevant fault based on the parameter passed 
 * @Parameters: Fault Type 
 * @Retval: None
 *
 */

void trigger_fault (FAULT_TYPE fault_type) ;

/*
 * @Brief : Generates stacking error during exception-entry
 * @Parameters: None 
 * @Retval: None
 *
 */

void bus_fault_stkerr(void) ; 

