/*
 * compass.h
 *
 * Created: 11/29/2017 12:12:13 AM
 *  Author:Jakkhad Timilsina
 */ 


#ifndef COMPASS_H_
#define COMPASS_H_

#include "I2C_NANO.h"
#include <math.h>

#define READ_ADDRESS	0X3D
#define WRITE_ADDRESS	0X3C

// 3, 16 bit-raw data for compass three direction
int16_t x_raw = 0, y_raw = 0, z_raw = 0;
I2C_NANO Hmc5883l;
int angle;

void init_compass()
{
	Hmc5883l.i2c_initialize();
	
	Hmc5883l.i2c_start(WRITE_ADDRESS);
	Hmc5883l.i2c_writedata(0x00);//set pointer CRA and no of data =8 at rate 15 hz
	Hmc5883l.i2c_writedata(0x70);
	Hmc5883l.i2c_stop();
	
	Hmc5883l.i2c_start(WRITE_ADDRESS);
	Hmc5883l.i2c_writedata(0x01);	//set pointer CRB and 0xA0
	Hmc5883l.i2c_writedata(0xA0);
	Hmc5883l.i2c_stop();
	
	Hmc5883l.i2c_start(WRITE_ADDRESS);
	Hmc5883l.i2c_writedata(0x02);
	Hmc5883l.i2c_writedata(0x00);	//continous measurement mode
	Hmc5883l.i2c_stop();
	uart0_puts("initialisation completed\n");
	
}

void readcompass_data()
{
	
	Hmc5883l.i2c_start(WRITE_ADDRESS);

	Hmc5883l.i2c_writedata(0x03); //set pointer to X-axis MSB
	Hmc5883l.i2c_stop();

	Hmc5883l.i2c_repStart(READ_ADDRESS);
	
		uart0_puts("initialise 1\n");
	x_raw = ((uint8_t)Hmc5883l.i2c_readACK())<<8;
	x_raw |= Hmc5883l.i2c_readACK();
	uart0_puts("initialise 2\n");
	
	z_raw = ((uint8_t)Hmc5883l.i2c_readACK())<<8;
	z_raw |= Hmc5883l.i2c_readACK();
	uart0_puts("initialise 3\n");
	
	y_raw = ((uint8_t)Hmc5883l.i2c_readACK())<<8;
	y_raw |= Hmc5883l.i2c_readNACK();
	uart0_puts("initialise 4\n");
	
	Hmc5883l.i2c_stop();

}

int Getcompass_angle()
{
	angle = ((180.0/3.1415)*atan2(y_raw,x_raw)+180);
	return angle;
}


#endif /* COMPASS_H_ */