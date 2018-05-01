/*
 * I2c.c
 *
 *  Created on: Dec 4, 2017
 *      Author: JorisJunior
 */
#include "I2c.h"

void init_i2c(void){
	Output_SCL;  /**/
	Output_SDA;  /**/
	SDA_High;   /**/
	SCL_High;  /**/
	delay(10);  
}

void delay (unsigned long delay){
	unsigned long i;
	for (i=0;  i<delay; ++i) {   /*Boucle d'attente*/
	}
}
void start_master_i2c(void){
	Output_SCL;/**/
	Output_SDA;
	SDA_Low;
	SCL_High;
	delay(1);
}

void stop_master_i2c(void){
	Output_SCL; /**/
	Output_SDA;	
	SDA_Low;
	SCL_Low;
	delay(1);
	SCL_High;
	delay(1);
	SDA_High;
	SCL_Low;
	delay(1);
	SCL_High;

}

void ack_from_master_i2c(void){
	SCL_Low;
	Output_SDA;
	delay(1);
	SCL_High;  /**/
	delay(1);
	SDA_Low;
	SCL_Low;
	delay(1);
}

void nack_from_master_i2c(void){
	delay(1);
	SCL_High;
	SDA_Low;
	delay(1);
	SCL_Low;
	
}

void ack_from_slave_i2c(void){
	SCL_Low;
	delay(1);
	SCL_High;
	delay(1);
	Input_SDA;
	while(SDA);  /* Attente de la réponse de l'esclave*/
	delay(2);
	SCL_High;
}



void read_byte_i2c(unsigned char *Read){
	unsigned char i;
	unsigned char bit;
	Input_SDA; /**/
	for (i=0; i<8; ++i) {  /**/
		bit=SDA;
		*Read<<=1;
		*Read|=bit&1;
		SCL_High;
		delay(1);
		SCL_Low;
		delay(1);
	}

}

void send_byte_i2c(unsigned char *Send){
	unsigned char i;
	Output_SDA;
	SCL_Low;
	for (i=0; i<8; ++i) {
		SDA=((*Send>>7-i)&1); /*Envoie bit par bit sur la ligne sda*/
		SCL_High;  /*Validation du bit */
		delay(1);
		SCL_Low;
		delay(1);
	}
	ack_from_slave_i2c();
}





