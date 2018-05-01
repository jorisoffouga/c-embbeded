/* ###################################################################
 **     Filename    : main.c
 **     Project     : bara_graph_click
 **     Processor   : MC9S08QE8CLC
 **     Version     : Driver 01.12
 **     Compiler    : CodeWarrior HCS08 C Compiler
 **     Date/Time   : 2018-04-28, 15:42, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.12
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */         
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Spi.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
void PWM(unsigned int periode,unsigned int value){
  TPM1C2SC=0x28;
  TPM1MOD=periode;       
  TPM1C2V=value;           
  TPM1SC=0x2A;          
}

void delay(unsigned long time){
  unsigned long i;
  for (i=0; i<= time; i++);
}

void BarGraph_Display(char value){
  spi BarGraph;
  unsigned char buffer[2]={0x00,0x00};
  char temp1, temp2;
  unsigned int temp;
  temp  = (1 << value) - 1;
  temp1 = (temp & 0x00FF);
  temp2 = (temp & 0xFF00) >> 8;
  buffer[0]=temp2;
  buffer[1]=temp1;
  init_spi_buffer(&BarGraph,buffer,2);
  spi_transfer(&BarGraph);
}
void BarGraph_chenillard(void){
  unsigned char i;
  for (i = 0; i < 11; ++i) {
      BarGraph_Display(i);
      delay(10000);
  }
  for (i = 10; i > 0; --i) {
      BarGraph_Display(i);
      delay(10000);
  }
}
void main(void){
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  volatile unsigned char value;
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  spi_init();
  PWM(10,10);
  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;){
      BarGraph_chenillard();
      
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
  PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale HCS08 series of microcontrollers.
 **
 ** ###################################################################
 */
