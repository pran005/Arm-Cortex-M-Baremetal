#include <stdint.h>

void disable_n_access_fpu(void) ; 
void enter_unpriv_mode(void) ; 
void enter_priv_mode(void) ; 
void enable_qei_interrupts(void) ; 
void bus_fault_precise(void); 
void bus_fault_imprecise(void) ;
void bus_fault_ibuserr(void) ; 
void mem_manage_iaccviol(void);
void usage_fault_invstate(void) ;
void usage_fault_undefinstr(void) ; 
void usage_fault_div_by_zero(void)  ; 
void usage_fault_invpc(void) ; 
void usage_fault_unaligned_mem_access(void) ; 
void trigger_fault (uint8_t fault_type) ;
void bus_fault_stkerr(void) ; 
