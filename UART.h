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


#ifndef UART_H_
#define UART_H_

/*******************************************************************/
/* Function Prototype Section
Add prototypes for all *** called by this module, with the exception
of runtime routines.
*******************************************************************/

/*******************************************************************
Function name   : void GPIO_for_UART_init()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Setup GPIO for UART
Notes           :
*******************************************************************/
void GPIO_for_UART_init();

/*******************************************************************
Function name   : void UART_init()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Initializes UART on the MSP430 board
Notes           :
*******************************************************************/
void UART_init();

/*******************************************************************
Function name   : void UART_transmit()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Transmit UART data
Notes           :
*******************************************************************/
void UART_transmit_data(uint8_t data);


#endif /* UART_H_ */
