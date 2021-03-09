/*****************************************************************
Module name: Interface for clock_and_timer

Copyright 2020-NTU/KVI
All Rights Reserved

The information contained herein is confidential property of Company.
The use, copying, transfer or disclosure of such information is
prohibited except by express written agreement with Company.

First written on 13/11/2020 by Srivatsan Ramasubramanian

Module Description:
Setup of clock and timer for the system. The clock is left at default
conditions of the board MSP430F5529. The timer A is used, with
three capture compare registers used to generate triggers for the
peripherals

*******************************************************************/

#ifndef CLOCK_AND_TIMER_H_
#define CLOCK_AND_TIMER_H_

/* Defines section
Add all #defines here
*******************************************************************/
#define SMCLKFREQ   8000000
#define SMCLKFREQPRE 125000
#define MCLKFREQ    8000000
#define ACLKFREQ    32000
#define USBCLKFREQ  4000000
#define SMCLKDIV    64
/*****************************************************************/

/* Function Prototype Section
Function name   : void clock_and_timer_config(uint16_t ADC_sampling_freq,uint16_t UART_sending_freq)
    returns     : nothing
    ADC_sampling_freq            : The sampling frequency for ADC
    UART_sending_freq            : The transmitting frequency for UART
Created by      : Srivatsan Ramasubramanian
Date created    : 18-Nov-2020
Description     : Initializes the clock with the default values of the board used
                  Uses timer A, sources SMCLK at 8 MHz to it. Generates three
                  trigger signals and corresponding interrupts for controlling
                  ADC and UART.
Notes           : The clock can be configured if this program is implemented on
                  a custom board
*******************************************************************/
void clock_and_timer_config(uint16_t ADC_sampling_freq,uint16_t UART_sending_freq);

/*******************************************************************
Function name   : void timer_start_counter(uint16_t base_address,uint16_t timer_mode)
returns     : nothing
base_address            : The base address of the timer to start counting
timer_mode              : The mode of counting of the timer
Created by      : Srivatsan Ramasubramanian
Date created    : 18-Nov-2020
Description     : Starts the counting of the timer in the necessary mode.
Notes           : Is there some way to get what timer is active?
*******************************************************************/

void timer_start_counter(uint16_t base_address,uint16_t timer_mode);


#endif /* HEADERS_CLOCK_AND_TIMER_H_ */
