/*
 * Compass.h
 *
 * Created: 6/13/2016 9:33:31 PM
 *  Author: user
 */ 


#ifndef COMPASS_H_
#define COMPASS_H_
#include <avr/io.h>
#include "TWI.h"

#define HMC5883L_WRITE 0x3C // write address  //7-bit address=0x1E
#define HMC5883L_READ 0x3D // read address

int16_t raw_x = 0;
int16_t raw_y = 0;
int16_t raw_z = 0;
int headingDegrees=0;

void init_HMC5883L(void){

	i2c_init();
	i2c_start(HMC5883L_WRITE);
	i2c_write(0x00); // set pointer to CRA 0x10
	i2c_write(0x70); // write 0x70 to CRA  Number of samples per output=8  ,data output rate=15
	i2c_stop();

	i2c_start(HMC5883L_WRITE);
	i2c_write(0x01); // set pointer to CRB  0x20
	i2c_write(0xA0); //gain=390  resolution(mg/LSB)=2.56  ,output= -2048-2047
	i2c_stop();

	i2c_start(HMC5883L_WRITE);
	i2c_write(0x02); // set pointer to measurement mode
	i2c_write(0x00); // continous measurement
	i2c_stop();
}

void read_Compass(void){

	i2c_start(HMC5883L_WRITE);
	i2c_write(0x03); //set pointer to X-axis MSB
	i2c_stop();

	i2c_rep_start(HMC5883L_READ);

	raw_x = ((uint8_t)i2c_readAck())<<8;
	raw_x |= i2c_readAck();
	
	raw_z = ((uint8_t)i2c_readAck())<<8;
	raw_z |= i2c_readAck();
	
	
	raw_y = ((uint8_t)i2c_readAck())<<8;
	raw_y |= i2c_readNak();
	
	i2c_stop();
}

float getHeading()
{
	read_Compass();
	// convert the raw data into a heading in degrees
	float headingDegrees1 = atan2((double)raw_y,(double)raw_x)* 180 / 3.14159265 + 180;
	return headingDegrees1;
}





#endif /* COMPASS_H_ */