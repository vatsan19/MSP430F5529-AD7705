/*****************************************************************
Module name: UART source file

Copyright 2020-NTU/KVI
All Rights Reserved

The information contained herein is confidential property of Company. 
The use, copying, transfer or disclosure of such information is
prohibited except by express written agreement with Company.

First written on 13/11/2020 by Srivatsan Ramasubramanian

Module Description:
Consists of the information for UART source files

*******************************************************************/
/* Include section
Add all #includes here
*******************************************************************/
#include "UART.h"

void GPIO_for_UART_init()
{
    // Set GPIO for alternate function
    GPIO_setAsPeripheralModuleFunctionInputPin(UART_PORT, UART_RECEIVE_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(UART_PORT, UART_TRANSMIT_PIN);//?
}

void UART_init()
{
    USCI_A_UART_initParam param1 = {0};
    param1.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
    param1.clockPrescalar = 6; // Values for 9600 baud rate
    param1.firstModReg = 13; // Values for 9600 baud rate
    param1.secondModReg = 0; // Values for 9600 baud rate
    param1.parity = USCI_A_UART_NO_PARITY;
    param1.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param1.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param1.uartMode = USCI_A_UART_MODE;
    param1.overSampling = USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;

    if (STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param1)){
        return;
    }

    //Enable UART module for operation
    USCI_A_UART_enable(USCI_A1_BASE);
    USCI_A_UART_enableInterrupt(USCI_A1_BASE, UCRXIE);
}

void UART_transmit_data(uint8_t data)
{
    while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, UCTXIFG));
    USCI_A_UART_transmitData(USCI_A1_BASE,data);

}
