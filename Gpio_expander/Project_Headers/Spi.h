/*
 * Spi.h
 *
 *  Created on: Mar 9, 2018
 *      Author: Joris OFFOUGA
 */

#ifndef SPI_H_
#define SPI_H_

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#define NULL ((void*)0)
#define NB_DATA 12
#define Ncs_1 PTBD_PTBD5
#define Ncs_2 PTAD_PTAD2

typedef struct{
  unsigned char buffer[NB_DATA];
  unsigned char *p_write;
  unsigned char *p_read;
  unsigned char nb_data;
}spi;

void spi_init(void);
void init_spi_buffer(spi *spi_buffer,unsigned char *buffer,unsigned char nb_data);
void spi_transfer(spi *spi_buffer);
void delai(unsigned short time);

#endif /* SPI_H_ */
