/*
 * Spi.c
 *
 *  Created on: Mar 9, 2018
 *      Author: Joris OFFOUGA
 */

#include "Spi.h"

void spi_init(void){
  PTBDD_PTBDD5=1;
  PTADD_PTADD2=1;
  SPIBR=0x04;
  SPIC2_MODFEN=0;
  SPIC1_SSOE=0;
  SPIC1_CPHA=1;
  SPIC1_CPOL=1;
  SPIC1_MSTR=1;
  SPIC1_SPE=1;
  PTBPE_PTBPE2=1;
  PTBPE_PTBPE3=1;
  PTBPE_PTBPE4=1;
  PTBPE_PTBPE5=1;
  PTBD_PTBD5=1;
  
}

void init_spi_buffer(spi *spi_buffer,unsigned char *buffer,unsigned char nb_data){
  unsigned char n=0,i=0;
  spi_buffer->p_read=NULL;
  spi_buffer->p_write=NULL;
  for (i = 0; i < NB_DATA; ++i) {
      spi_buffer->buffer[i]=0;
  }
  for (i=0; i<nb_data; ++i) {
      spi_buffer->buffer[i]=buffer[i];
  }
  spi_buffer->p_read=spi_buffer->buffer;
  spi_buffer->p_write=&(spi_buffer->buffer[5]);
  spi_buffer->nb_data=nb_data;
}


void spi_transfer(spi *spi_buffer){
  PTBD_PTBD5=0;
  while (spi_buffer->nb_data!=0){
      if (SPIS_SPTEF) {
          SPID=*spi_buffer->p_read;
          delai(35);
      }
      if((spi_buffer->p_read++)==(&spi_buffer->buffer[NB_DATA-8])){
          spi_buffer->p_read=spi_buffer->buffer;
      }
      if (SPIS_SPRF) {
          *spi_buffer->p_write=SPID;
      }
      if((spi_buffer->p_write++)==(&spi_buffer->buffer[NB_DATA-1])){
          spi_buffer->p_write=spi_buffer->buffer;
      }

      spi_buffer->nb_data--;
  }
  PTBD_PTBD5=1;
}


void delai(unsigned short time){
  unsigned short i;
  for (i = time; i > 0; i--) {
  }
}

