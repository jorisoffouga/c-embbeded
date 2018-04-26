/*
 * gpio_expander.c
 *
 *  Created on: Apr 26, 2018
 *      Author: Joris OFFOUGA 
 */

#include "gpio_expander.h"

gpio_expander expander;

void port_dir(unsigned char dir){
  unsigned char buffer[3]={ADDRESS_W,IODIR,0x00};
  buffer[2]=dir;
  init_spi_buffer(&expander.expander,buffer,3);
  spi_transfer(&expander.expander);
}


void gpio_pin_write(unsigned pin,unsigned char dir){
  expander.port_expander.data_port=read_register(GPIO);
  if(dir){
      expander.port_expander.data_port=expander.port_expander.data_port & ~(1 << pin);
  }else{
      expander.port_expander.data_port=expander.port_expander.data_port | (1<<pin);
  }
  write_register(GPIO,expander.port_expander.data_port);
}


void write_expander(unsigned char value){
  unsigned char buffer[3]={ADDRESS_W,GPIO,0x00};
  buffer[2]=value;
  init_spi_buffer(&expander.expander,buffer,3);
  spi_transfer(&expander.expander);
}

unsigned char read_register(unsigned char reg){
  unsigned char buffer[3]={ADDRESS_R,0x00,0x00};
  buffer[1]=reg;
  init_spi_buffer(&expander.expander,buffer,3);
  spi_transfer(&expander.expander);
  return expander.expander.buffer[7];
}

void write_register(unsigned char reg,unsigned char value){
  unsigned char buffer[4]={ADDRESS_W,0x00,0x00,0x00};
  buffer[1]=reg;
  buffer[2]=value;
  init_spi_buffer(&expander.expander,buffer,4);
  spi_transfer(&expander.expander);
}
