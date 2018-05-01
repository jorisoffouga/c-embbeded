/* ###################################################################
 **     Filename    : main.c
 **     Project     : TP_I2C
 **     Processor   : MC9S08QE8CLC
 **     Version     : Driver 01.12
 **     Compiler    : CodeWarrior HCS08 C Compiler
 **     Date/Time   : 2017-12-04, 16:11, # CodeGen: 0
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
#include "Cpu.h"
#include "Events.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "I2c.h"



/* User includes (#include below this line is not maintained by Processor Expert) */





void main(void){
	/* Write your local variable definition here */

	unsigned char adress_write=0x90;
	unsigned char adress_read=0x41;
	unsigned char config_write=0x40;
	unsigned char config_read=0x00;
	unsigned char data0=0x7F;
	unsigned char data1=0x30;
	unsigned char bit0=0;
	unsigned char bit1=0;
	unsigned char bit2=0;
	unsigned char bit3=0;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/


	init_i2c();
	for(;;){
		start_master_i2c();
		send_byte_i2c(&adress_write);	
		send_byte_i2c(&config_write);
		//send_byte_i2c(&adress_read);
		send_byte_i2c(&data0);
		//send_byte_i2c(&data1);
		/*
		read_byte_i2c(&bit0);
		ack_from_master_i2c();
		read_byte_i2c(&bit1);
		ack_from_master_i2c();
		read_byte_i2c(&bit2);
		ack_from_master_i2c();
		read_byte_i2c(&bit3);
		ack_from_master_i2c();
		nack_from_master_i2c();
		 */
		stop_master_i2c();

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
