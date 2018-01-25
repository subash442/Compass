/* 
* I2C_NANO.h
*
* Created: 11/27/2017 4:41:47 PM
* Author: JAkkhad Timilsina
*/


#ifndef __I2C_NANO_H__
#define __I2C_NANO_H__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "uart.h"
#define SCALE_FACTOR		1

#define SCL_CLK		100000UL
#define TWBR_VAL	((F_CPU/SCL_CLK)-16)/(2*SCALE_FACTOR)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

class I2C_NANO
{
	private:
	
	
	public:
	void i2c_initialize();
	void i2c_stop();
	bool i2c_start(unsigned char addr);
	bool i2c_repStart(unsigned char addrss);
	bool i2c_writedata(unsigned char data);
	unsigned char i2c_readACK();
	unsigned char i2c_readNACK();

};
#endif //__I2C_NANO_H__
