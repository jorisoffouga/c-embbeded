/*
 * I2c.h
 *
 *  Created on: Dec 4, 2017
 *      Author: JorisJunior
 */

#ifndef I2C_H_
#define I2C_H_

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"


#define SDA PTAD_PTAD2  
#define SCL PTAD_PTAD3

#define SDA_High PTAD_PTAD2=1 	
#define SCL_High PTAD_PTAD3=1

#define SDA_Low	PTAD_PTAD2=0 	
#define SCL_Low PTAD_PTAD3=0

#define Output_SDA PTADD_PTADD2=1
#define Input_SDA PTADD_PTADD2=0

#define Output_SCL PTADD_PTADD3=1
#define Input_SCL PTADD_PTADD3=0

#define ACK 0
#define NACK 1

void init_i2c(void); /**/
void start_master_i2c(void); /**/
void stop_master_i2c(void); /**/
void ack_from_master_i2c(void); /**/
void nack_from_master_i2c(void); /**/
void ack_from_slave_i2c(void); /**/
void read_byte_i2c(unsigned char *octet); /**/
void send_byte_i2c(unsigned char *octet); /**/
void delay (unsigned long );

#endif /* I2C_H_ */
