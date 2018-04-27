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


void gpio_pin_write(unsigned char pin,unsigned char value){
  expander.port_expander.data_port=~(read_register(GPIO));
  if(value){
      expander.port_expander.data_port=(expander.port_expander.data_port | (1<<pin)); /* pin high */
  }else{
      expander.port_expander.data_port=(expander.port_expander.data_port & ~(1 << pin)); /* pin low */
  }
  expander.port_expander.data_port=~(expander.port_expander.data_port & (1 << pin));
  write_register(GPIO,expander.port_expander.data_port);
}

unsigned char gpio_pin_read(unsigned char pin){
  expander.port_expander.data_port=~(read_register(GPIO));
  expander.port_expander.data_port=(expander.port_expander.data_port & (1 << pin));
  return expander.port_expander.data_port;
}

unsigned char read_register(unsigned char reg){
  unsigned char buffer[3]={ADDRESS_R,0x00,0x00};
  buffer[1]=reg;
  init_spi_buffer(&expander.expander,buffer,3);
  spi_transfer(&expander.expander);
  return expander.expander.buffer[7];
}

void write_register(unsigned char reg,unsigned char value){
  unsigned char buffer[3]={ADDRESS_W,0x00,0x00};
  buffer[1]=reg;
  buffer[2]=value;
  init_spi_buffer(&expander.expander,buffer,3);
  spi_transfer(&expander.expander);
}

void delay(unsigned long time){
  unsigned long i;
  for (i=0; i<= time; i++);
}

/*function test, gpio_expander branch to 8 led control in inverse */
void chenillard (void){
  unsigned char i,j;
  write_register(GPIO,0xFF);
  for (i = 0; i < 8; ++i) {
      for (j = 0; j < 2; ++j) {
          gpio_pin_write(i,j);
          delay(10000);
      }
  }
  for (i = 7; i > 0; i--) {
        for (j = 0; j < 2; ++j) {
            gpio_pin_write(i,j);
            delay(10000);
        }
    }
}
