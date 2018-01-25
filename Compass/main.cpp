/*
 * Compass.cpp
 *
 * Created: 11/27/2017 4:23:02 PM
 * Author : Subash Timilsina
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "compass.h"
#include "uart.h"

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

int main(void)
{
	sei();
	  uart0_init(UART_BAUD_SELECT(9600,F_CPU));
	init_compass();
 
    while (1) 
    {
		readcompass_data();
		uart0_putint(Getcompass_angle());
		uart0_putc('\n');
		
    }
}

