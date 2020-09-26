A small project that fires System Exceptions for Arm Cortex-M3(and onwards) devices through Software. 

![Terminal](https://github.com/pran005/Arm-Cortex-M-Baremetal/blob/master/Cortex_M_faults/Terminal.PNG)

Note: In Bus Fault Exception the STKERR sub-type is implemented by using up the entire SRAM. Any function calls in the Fault Handler may lead CPU to a lockup state.
      This has been taken care of in this example by entering into an infinite loop in case a STKERR is detected. Derivatives of this code example shall take appropriate actions. 
      
The code can be reused for any ARM-Cortex M3 (and onwards) devices, with a slight exception : 
  
  1. This code example uses a Tiva C Eval Kit: EK-TM4C123GXL. 
     One peripheral interrupt (QEI) generated in order to fire an exception is specific to this device. 
  
  2. The Debug prints are taken over UART0 which, again is specific to this device. 
  
In order to use this code example for any other device the above points shall be worked upon for achieving similar functionality. 

     
