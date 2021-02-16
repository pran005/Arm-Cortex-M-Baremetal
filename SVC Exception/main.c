int __svc(0x00) service_Add (int a, int b) ; // __svc is a compiler keyword that replaces a function call with an SVC instruction containing the specified number.
int __svc(0x01) service_sub (int a, int b) ;
int __svc(0x02) service_mult (int a, int b) ;
int __svc(0x03) service_div (int a, int b) ;
void SVC_Handler_C(unsigned int *svc_args) ; 

int x,y,z ; 
int main()
{
    x= 1 ; 
    y= 5 ; 
    z= service_Add(x,y) ;  

	x = 9 ;
	y= 2 ; 
	z = service_sub(x,y) ; 

	x=3;
	y=4 ; 
	z = service_mult(x,y) ;

	x=28;
	y=4 ; 
	z = service_div(x,y) ;	
}

__asm void SVC_Handler(void)
{	
	TST LR,#4 // check bit 2
		
	ITE EQ 
	MRSEQ R0,MSP				// if bit 2 is 0 	
	MRSNE R0,PSP    	       // if bit 2 is not 0 
	B __cpp(SVC_Handler_C) 

}

void SVC_Handler_C(unsigned int *svc_args)
{
	unsigned int svc_num ;
	/* extract SVC number from PC */  
	svc_num = ((char*)svc_args[6])[-2] ; 			 
	switch(svc_num)
	{

		/* AAPCS : Func parameters are stored in R0-R3 & retval in R0, args[0] -> R0 (of caller) & args[1] -> R1 (of caller)  */ 

		case 0 : 
			svc_args[0] = svc_args[1] + svc_args[0] ; 						
			break ; 
		case 1 : 
			svc_args[0] = svc_args[0] - svc_args[1] ; 					
			break ; 
		case 2 : 
			svc_args[0] = svc_args[1] * svc_args[0] ; 					
			break ;
		case 3 : 
			svc_args[0] = svc_args[0] / svc_args[1] ; 
			break ;		
		default : 
			break ; 
	}
}
