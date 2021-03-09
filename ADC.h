/*****************************************************************
Module name: Interface for ADC

Copyright 2020-NTU/KVI
All Rights Reserved

The information contained herein is confidential property of Company.
The use, copying, transfer or disclosure of such information is
prohibited except by express written agreement with Company.

First written on 18/01/2020 by Srivatsan Ramasubramanian

Module Description:
This is the headerfile for the ADC module. It contains the prototypes
that define both the interfaces and the internal functions of the
ADC module

*******************************************************************/
/* Include section
Add all #includes here*/

#include "driverlib.h"
#include "defines.h"

/*******************************************************************/
/* Defines section*/
#ifndef ADC_H_
#define ADC_H_
/*******************************************************************/
/* Function Prototype Section
Add prototypes for all *** called by this module, with the exception
of runtime routines.
*******************************************************************/

/*******************************************************************
Function name   : void ADC_init()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : 1. Write to communications register selecting channel
                     set up next operation to be a write to clock register
                  2. Write to clock register setting the clock bits in
                     accordance  with the applied master clock
                  3. Write to communications register selecting channel
                     and setting up next operation to be a write to
                     a setup register
                  4. Write to setup register clearing F sync, setting up
                     gain, operating conditions and initiate a self
                     calibration on selected channel
Notes           : Communication register bit information
                  bit 8  : 0 if writing otherwise DRDY
                  bit 7-5: Register being accessed in this write operation. Refer
                         to manual for the values for each registers
                  bit 4  : Selects if next operation is read or write
                  bit 3  : Standby if 1
                  bit 2-1: Channel selection
*******************************************************************/
void ADC_init(uint8_t channel,uint8_t clkDivider,uint8_t polarity,uint8_t gain,uint8_t updRate);


/******************************************************************
 * Function name: void ADC_reset()
 *  returns     : nothing
 * Created by   : Srivatsan Ramasubramanian
 * Date created : 08/03/2021
 * Description  : Resets the ADC by sending 0xFF
 */
void ADC_reset();

/******************************************************************
 * Function name: void setNextOperation()
 *  returns     : nothing
 * Created by   : Srivatsan Ramasubramanian
 * Date created : 08/03/2021
 * Description  :
 */
void setNextOperation(uint8_t reg,uint8_t channel,uint8_t readWrite);

/******************************************************************
 * Function name: void setNextOperation()
 *  returns     : nothing
 * Created by   : Srivatsan Ramasubramanian
 * Date created : 08/03/2021
 * Description  :
 */
void writeClockRegister(uint8_t CLKDIS,uint8_t CLKDIV,uint8_t outputUpdateRate);

/******************************************************************
 * Function name: void setNextOperation()
 *  returns     : nothing
 * Created by   : Srivatsan Ramasubramanian
 * Date created : 08/03/2021
 * Description  :
 */
void writeSetupRegister(uint8_t operationModer,uint8_t gain,uint8_t unipolar,uint8_t buffered,uint8_t fsync);
/*******************************************************************
Function name   : void ADC_respond()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : 1. Write to communication register to mention that you are querying the status register
                  2. Query status register
Notes           : Communication register bit information
                  bit 8  : 0 if writing otherwise DRDY
                  bit 7-5: Register being accessed in this write operation. Refer
                         to manual for the values for each registers
                  bit 4  : Selects if next operation is read or write
                  bit 3  : Standby if 1
                  bit 2-1: Channel selection
*******************************************************************/
uint8_t ADC_is_running();


/*******************************************************************
Function name   : bool isDRDY()
    returns     : nothing
    arg1            : nothing
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Checks if data is ready to be transferred to the MCU
Notes           : Need to read more about other configurations
*******************************************************************/
bool is_DRDY(uint8_t channel);

/*******************************************************************
Function name   : uint16_t ADC_retrievedata()
    returns     : the data retrieved from ADC
    arg1            : 'data' to be sent through UART
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Get data from ADC
Notes           :
*******************************************************************/
uint16_t ADC_retrievedata(uint8_t channel,uint8_t refOffset);

/*******************************************************************
Function name   : uint16_t readADResult()
    returns     : the data retrieved from ADC
    arg1            : 'data' to be sent through UART
Created by      : Srivatsan Ramasubramanian
Date created    : 18/01/2020
Description     : Get data from ADC
Notes           :
*******************************************************************/
uint16_t readADResult();
#endif /* ADC_H */
