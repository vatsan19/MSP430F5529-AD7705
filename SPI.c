/*****************************************************************
Module name: 

Copyright 2020-NTU/KVI
All Rights Reserved

The information contained herein is confidential property of Company. 
The use, copying, transfer or disclosure of such information is
prohibited except by express written agreement with Company.

First written on 13/11/2020 by Srivatsan Ramasubramanian

Module Description:
(fill in a detailed description of the module's function here)

*******************************************************************/
/* Include section
Add all #includes here*/
#include "SPI.h"
#include "defines.h"
#include "driverlib.h"
/*******************************************************************/
/* Defines section
Add all #defines here
*******************************************************************/
uint8_t returnValue = 0x00;
uint8_t transmitData = 0x00, receiveData=0xFF;
/* Function Prototype Section
Add prototypes for all *** called by this module, with the exception
of runtime routines.
*******************************************************************/
void GPIO_for_SPI_init()
{
    /*
     * Setup GPIO pins
     */
        //Set Reset pin as output pin
        GPIO_setAsOutputPin(RESET_PORT, RESET_PIN);

        //Set LED1 pin as output pin
        GPIO_setAsOutputPin(LED1_PORT,LED1_PIN);

        // Set CS pin as output pin
        GPIO_setAsOutputPin(SPI_CS_PORT,SPI_CS_PIN);

        //Set high on CS pin
        GPIO_setOutputHighOnPin(SPI_CS_PORT, SPI_CS_PIN);

        GPIO_setAsInputPin(DRDY_PORT, DRDY_PIN);

        // Set SOMI
        GPIO_setAsPeripheralModuleFunctionInputPin(SPI_PORT, SPI_SOMI_PIN);

        // Set SIMO and SCLK
        GPIO_setAsPeripheralModuleFunctionOutputPin(SPI_PORT, SPI_SIMO_PIN);
        GPIO_setAsPeripheralModuleFunctionOutputPin(SPI_PORT, SPI_SCLK_PIN);

        //GPIO_setAsPeripheralModuleFunctionInputPin(SPI_PERIPHERAL);


}
/*******************************************************************
Function name   : void SPI_init()
*******************************************************************/
void SPI_init()
{
    //Initialize Master SPI
    USCI_B_SPI_initMasterParam param = {0};
    param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK; // SMCLK as clock source
    param.clockSourceFrequency = UCS_getSMCLK(); // Clock source frequency
    param.desiredSpiClock = SPICLK/2; // Choose SPICLK as clock for SPI
    param.msbFirst = USCI_B_SPI_MSB_FIRST; // Send MSB first
    param.clockPhase = USCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT; // Assume this is CPHA = 1
    param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH; // Set clock to high when inactive
    returnValue =  USCI_B_SPI_initMaster(USCI_B0_BASE, &param); // SPI initialization


    if (STATUS_FAIL == returnValue){
        return;
    }
    /* SPI enable
     * 1. Enable the SPI peripheral
     * 2.
     * 3. Remove the reset signal
     * 4. Turn on LED
     * 5. Wait until ADC initializes
     * 6. Start timer and enable the capture compare interrupt
     */
    SPI_enable();

}

void SPI_enable()
{
    /*Reset input driven low
    GPIO_setOutputLowOnPin(RESET_PORT, RESET_PIN);
    __delay_cycles(10);
    while(GPIO_getInputPinValue(DRDY_PORT, DRDY_PIN)); // Turns low when reset is done
    GPIO_setOutputHighOnPin(RESET_PORT, RESET_PIN);*/

    //Enable SPI module
    USCI_B_SPI_enable(USCI_B0_BASE);

    //Enable receive and transmit interrupts
    // I think this is not necessary. If it is
    // there we need to setup interrupt tables
    //Receive interrupt
   /* USCI_A_SPI_clearInterrupt(USCI_B0_BASE,
        USCI_B_SPI_RECEIVE_INTERRUPT);
    USCI_A_SPI_enableInterrupt(USCI_B0_BASE,
        USCI_B_SPI_RECEIVE_INTERRUPT);

    // Transmit interrupt
    USCI_A_SPI_clearInterrupt(USCI_B0_BASE,
        USCI_A_SPI_TRANSMIT_INTERRUPT);
    USCI_A_SPI_enableInterrupt(USCI_B0_BASE,
        USCI_A_SPI_TRANSMIT_INTERRUPT);*/





    //LED On
    GPIO_setOutputHighOnPin(
        LED1_PORT,
        LED1_PIN
        );

    //Wait for slave to initialize



}

uint8_t SPI_send_data_to_slave(uint8_t data)
{
    //TXIFG: It will be set when the transmit buffer is empty.
    //RXIFG: It will be set when receive buffer is full
    uint8_t return_data=0x21;



    // TX buffer ready?
    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, UCTXIFG));
    USCI_B_SPI_transmitData(USCI_B0_BASE,data);
    while(USCI_B_SPI_isBusy(USCI_B0_BASE)); // Check if any transmission is happening



    return_data=SPI_receive_data_from_slave();

    return return_data;



}

uint8_t SPI_receive_data_from_slave()
{



    //while(USCI_B_SPI_isBusy(USCI_B0_BASE));

    receiveData = USCI_B_SPI_receiveData(USCI_B0_BASE);


    return receiveData;
}
