/*
 * gpio_expander.h
 *
 *  Created on: Apr 26, 2018
 *      Author: Joris OFFOUGA
 */

#ifndef GPIO_EXPANDER_H_
#define GPIO_EXPANDER_H_

#include "spi.h"

#define  ADDRESS_W  0x40 
#define  ADDRESS_R  ADDRESS_W+1
#define  IOCON     0x05
#define  IODIR     0x00
#define  GPPU      0x06
#define  GPIO      0x09
#define  GPINTEN   0x02
#define  IPOL      0x01
#define  DEFVAL    0x03
#define  INTF      0x07
#define  INTCAP    0x08
#define  OLAT      0x0A
#define  INTCON    0x04

typedef union{
  unsigned char data_port;
  struct{
  unsigned char pin1 :1;
  unsigned char pin2 :1;
  unsigned char pin3 :1;
  unsigned char pin4 :1;
  unsigned char pin5 :1;
  unsigned char pin6 :1;
  unsigned char pin7 :1;
  unsigned char pin8 :1;
  }port_bit;
}port;

typedef struct{
  spi expander;
  port port_expander;
}gpio_expander;

unsigned char read_register(unsigned char reg);
void write_expander(unsigned char value);
void write_register(unsigned char reg,unsigned char value);
void gpio_pin_write(unsigned pin,unsigned char dir);
void port_dir(unsigned char dir);

#endif /* GPIO_EXPANDER_H_ */
