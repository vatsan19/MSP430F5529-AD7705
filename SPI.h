/*****************************************************************
Module name: Interface for SPI

Copyright 2020-NTU/KVI
All Rights Reserved

The information contained herein is confidential property of Company.
The use, copying, transfer or disclosure of such information is
prohibited except by express written agreement with Company.

First written on 18/01/2020 by Srivatsan Ramasubramanian

Module Description:
This is the headerfile for the UART module. It contains the prototypes
that define both the interfaces and the internal functions of the
UART module

*******************************************************************/
/* Include section
Add all #includes here*/

#include "driverlib.h"
#include "defines.h"
/*******************************************************************/
/* Defines section*/
#ifndef SPI_H_
#define SPI_H_
/*******************************************************************/
/* Function Prototype Section
Add prototypes for all *** called by this module, with the exception
of runtime routines.
*******************************************************************/
/*******************************************************************
Function name   : void GPIO_for_SPI_init()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Initializes the GPIO pins for SPI configuration
Notes           : Need to read more about other configurations
*******************************************************************/
void GPIO_for_SPI_init();

/*******************************************************************
Function name   : void SPI_init()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Initializes the UART in the MSP430EXPF5529 board.
                  Here are the chosen UART parameters
                  Clock source      : SMCLK
                  Clock prescaler   : 109
                  firstmodreg       : For fractional baud rate support
                  secondmodreg      : For fractional baud rate support
                  parity            : no parity bit
                  msborlsbfirst     : Which bit is sent first by UART
                  numberofstopbits  : one stop bit
                  UART mode         : Default UART mode
                  oversampling      : low frequency baud rate generation
Notes           : Need to read more about other configurations
*******************************************************************/
void SPI_init();

/*******************************************************************
Function name   : void SPI_enable()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Enables the SPI board and the receive interrupt of SPI
                  shifts the reset signal
Notes           : Need to read more about other configurations
*******************************************************************/
void SPI_enable();

/*******************************************************************
Function name   : void SPI_send_data_to_PC(uint8_t data)
    returns     : nothing
    arg1            : 'data' to be sent through UART
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Transmits 8 bit data to the computer. This is why
                  often, data is sent in the form of strings
Notes           :
*******************************************************************/
uint8_t SPI_send_data_to_slave(uint8_t data);

/*******************************************************************
Function name   : uint16_t SPI_receive_data_from_slave()
    returns     : received data
    arg1            :
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Receives data from slave
Notes           :
*******************************************************************/
uint8_t SPI_receive_data_from_slave();

#endif /* SPI_H_ */
