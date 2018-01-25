/* 
* I2C_NANO.cpp
*
* Created: 11/27/2017 4:41:47 PM
* Author: Jakkhad Timilsina
*/


#include "I2C_NANO.h"


void I2C_NANO::i2c_initialize()
{
	TWBR = TWBR_VAL;		//prescaler 1 with 100khz clk cycle
}

void I2C_NANO::i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);		//stop bit set
	//wait until twi is stopped.
	
	while(TWCR & (1<<TWSTO));
}

bool I2C_NANO::i2c_start(unsigned char addr)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);		//start bit set
	
	//wait until transmitting
	
	while(!(TWCR & (1<<TWINT))); //TWINT 0 while transmitting and 1 after transmitting and wait for response
	
	if(((TWSR & 0xF8)!=0x10)&&((TWSR & 0xF8)!=0x08))	return 1;	//checking the status if the start or repeated condition is issued or not
	
	TWDR = addr;	//adding address on twi data register
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	//for ack or nack signal 
	//wait until transmission
	while(!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8)!=0x18 && (TWSR & 0xF8)!=0x40)	return 1;		//master write and ack signal check
	return 0;
}

bool I2C_NANO::i2c_repStart(unsigned char addrss)
{
	return i2c_start(addrss);
}

bool I2C_NANO::i2c_writedata(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
	
	if ((TWSR & 0xF8) != 0x28) return 1; //data sent and ack received 
	return 0;	
}

unsigned char I2C_NANO::i2c_readACK()
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);//ack enable
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

unsigned char I2C_NANO::i2c_readNACK()
{
	TWCR = (1<<TWEN) | (1<<TWINT);// ack disable
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}