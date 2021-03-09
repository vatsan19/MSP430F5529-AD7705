/*****************************************************************
Module name: ADC source file

Copyright 2020-NTU/KVI
All Rights Reserved

The information contained herein is confidential property of Company. 
The use, copying, transfer or disclosure of such information is
prohibited except by express written agreement with Company.

First written on 13/11/2020 by Srivatsan Ramasubramanian

Module Description:
Consists of the definitions for the function to control the AD7705
ADC

*******************************************************************/
/* Include section
Add all #includes here
*******************************************************************/
#include "ADC.h"
#include "SPI.h"
#include "defines.h"
/* Defines section
Add all #defines here
*/
uint8_t initialization_data=0x00;
uint8_t response_data=0xFF;
/*******************************************************************/
/* Function Prototype Section
*******************************************************************/
void ADC_init(uint8_t channel,uint8_t clkDivider,uint8_t polarity,uint8_t gain,uint8_t updRate)
{

    setNextOperation(REG_CLOCK, channel, 0);
    writeClockRegister(0, clkDivider, updRate);

    setNextOperation(REG_SETUP, channel, 0);
    writeSetupRegister(MODE_SELF_CAL, gain, polarity, 0, 0);

    while (!is_DRDY(channel));

}

void setNextOperation(uint8_t reg,uint8_t channel,uint8_t readWrite)
{
    uint8_t r=0x00;
    r=reg<<4|readWrite<<3|channel;

    GPIO_setOutputLowOnPin(SPI_CS_PORT, SPI_CS_PIN);
    SPI_send_data_to_slave(r);
    GPIO_setOutputHighOnPin(SPI_CS_PORT, SPI_CS_PIN);
}

void writeClockRegister(uint8_t CLKDIS,uint8_t CLKDIV,uint8_t outputUpdateRate)
{
    uint8_t r=CLKDIS<<4|CLKDIV<<3|outputUpdateRate;
    r&=~(1<<2); // Clear CLK

    GPIO_setOutputLowOnPin(SPI_CS_PORT, SPI_CS_PIN);
    SPI_send_data_to_slave(r);
    GPIO_setOutputHighOnPin(SPI_CS_PORT, SPI_CS_PIN);

}

void writeSetupRegister(uint8_t operationModer,uint8_t gain,uint8_t unipolar,uint8_t buffered,uint8_t fsync)
{
    uint8_t r=operationModer<<6|gain<<3|unipolar<<2|buffered<<1|fsync;
    GPIO_setOutputLowOnPin(SPI_CS_PORT, SPI_CS_PIN);
    SPI_send_data_to_slave(r);
    GPIO_setOutputHighOnPin(SPI_CS_PORT, SPI_CS_PIN);
}

uint8_t ADC_is_running()
{


    uint8_t x=0xFF;
    //Write to communication register, selecting the test register and reading from it

    initialization_data=0b01001000;
   // while(USCI_B_SPI_isBusy(USCI_B0_BASE));
   // y=SPI_send_data_to_slave(initialization_data);


    __delay_cycles(100);

    //Write to communication register, selecting the setup register and reading from it
   // initialization_data=0b00011000;
    //initialization_data=0b00100000;
    while(USCI_B_SPI_isBusy(USCI_B0_BASE));
    x=SPI_send_data_to_slave(initialization_data);


    return x;




}

bool is_DRDY(uint8_t channel)
{
    bool response;
    setNextOperation(REG_CMM,channel,1);
    GPIO_setOutputLowOnPin(SPI_CS_PORT, SPI_CS_PIN);
    response=SPI_send_data_to_slave(0x0);
    GPIO_setOutputHighOnPin(SPI_CS_PORT, SPI_CS_PIN);

    return (response&0x80)==0x0;


}

uint16_t readADresult()
{
    GPIO_setOutputLowOnPin(SPI_CS_PORT, SPI_CS_PIN);
    uint8_t b1=SPI_send_data_to_slave(0x00);
    uint8_t b2=SPI_send_data_to_slave(0x00);
    GPIO_setOutputHighOnPin(SPI_CS_PORT, SPI_CS_PIN);

    uint16_t r=b1<<8|b2;
    return r;
}

uint16_t ADC_retrievedata(uint8_t channel,uint8_t refOffset)
{
    while(!is_DRDY(channel));
    setNextOperation(REG_DATA, channel, 1);

    return readADresult();
}


void ADC_reset()
{
    uint8_t reset_data=0xFF;
    volatile int i=0;

    for(i=0;i<100;i++)
    {
        GPIO_setOutputLowOnPin(SPI_CS_PORT, SPI_CS_PIN);
        SPI_send_data_to_slave(reset_data);
        GPIO_setOutputHighOnPin(SPI_CS_PORT, SPI_CS_PIN);
    }
}
