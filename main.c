#include "driverlib.h"
#include "SPI.h"
#include "ADC.h"
#include "Clock_and_timer.h"
#include "UART.h"
#include "string.h"
#include "stdio.h"
#include "defines.h"
uint8_t *ADCdata;
uint16_t act_data=920;
char stringtosend[40];
char *stringfail="Please enter '?'\r\n";
uint8_t rData=0xFF;
uint8_t tData=0xFF;
volatile uint8_t i=0;
uint8_t response=0xFF;
/*      MSP430F5529                                      AD7705
 *  --------------------                        ---------------------
 * |                    |                      |                     |
 * |    P1.5-Slave Reset|                      |RS                   |
 * |            P2.0-CS |----------------------|CS                   |
 * |      P3.0-UCB0SIMO |----------------------|DIN                  |
 * |      P3.1-UCB0SOMI |----------------------|DOUT                 |
 * |      P3.2-UCB0SCLK |----------------------|SCK                  |
 * |                    |                      |________Vcc____GND___|
 * |                    |                                |      |
 * |            5V      | -------------------------------|      |
 * |____________GND_____|---------------------------------------|
 *
 * Notes
 * P1.5 is the slave reset button. It resets the setting of AD7705 if it is pulled low.
 * P2.0 is the chip select button. If this is pulled low, the chip is selected low.
 * P3.0 serial data is written to the input shift register on the part. Data from the input shift register is transferred to the setup register,
 * clock register, or communication register, depending on the register selection bits of the communication register
 * P3.1 is connected to DOUT of the ADC. The DOUT shift register contains information based on the selection of the communication register
 * P3.2 is connected to SCLK. This is the serial clock that comes from the master.
 */
void main()
{

    WDT_A_hold(WDT_A_BASE);
    // To select the timer frequencies
   // const uint16_t ADC_sampling_freq=100;
    //const uint16_t UART_sending_freq=100;
   // clock_and_timer_config(ADC_sampling_freq, UART_sending_freq);

/* SPI Initializer
 * 1. Sets P1.5 as reset output pin for the Slave
 * 2. Sets P2.0 as CS output PIN
 * 3. Sets P1.0 as LED output PIN
 * 5. Set SIMO, SOMI, SCLK pins to peripheral modules
 * 6. Initialize SPI master
 */
    GPIO_for_SPI_init();
    SPI_init();

    // This works
    GPIO_for_UART_init();









/*
 * ADC initializer
 * Software reset ADC by sending 0xff
 * Send information to the ADC to start it up
 */
    ADC_reset();
    ADC_init(CHN_AIN2,CLK_DIV_1,BIPOLAR,GAIN_1,UPDATE_RATE_500);

    //timer_start_counter(TIMER_A0_BASE, TIMER_A_UP_MODE);
    UART_init();


    __bis_SR_register(LPM0_bits+GIE);
    __no_operation();





}

/* Interrupt vector table*/
// UART interrupt
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{


    switch(__even_in_range(UCA1IV,4))
    {
        case 2:
            // Echo back RXed character, confirm TX buffer is ready first
            while(USCI_A_UART_queryStatusFlags(USCI_A1_BASE, UCBUSY));

            rData=USCI_A_UART_receiveData(USCI_A1_BASE);

            // Query setup register
            if((char)rData=='?')
            {
                //response=24;
                act_data=ADC_retrievedata(CHN_AIN2,0);

                sprintf(stringtosend,"The value is: %u \r\n",act_data);
                for(i=0;i<strlen(stringtosend);i++)
                {
                    tData=(uint8_t)*(stringtosend+i);
                    while(USCI_A_UART_queryStatusFlags(USCI_A1_BASE, UCBUSY));
                    while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, UCTXIFG));
                    USCI_A_UART_transmitData(USCI_A1_BASE,tData);
                }


            }

            else
            {
                for(i=0;i<strlen(stringfail);i++)
                {
                    tData=(uint8_t)*(stringfail+i);
                    while(USCI_A_UART_queryStatusFlags(USCI_A1_BASE, UCBUSY));
                    while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, UCTXIFG));
                    USCI_A_UART_transmitData(USCI_A1_BASE,tData);
                   // GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);


                }

            }


            break;

        default:

            break;



    }
}



/* Define interrupt for TIMER A0*/


/*#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer_ISR(void)
{

    //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
    switch ( __even_in_range(TA0IV,14) ){
            case  0: break;                          //No interrupt
            case  2:
                ADCdata=ADC_retrievedata();
                act_data=((*ADCdata)<<8)|(*(ADCdata+1)&0xff);
                GPIO_toggleOutputOnPin(LED1_PORT, LED1_PIN);
                break;                               //CCR1 not used
            case  4:
                break;                          //CCR2 not used
            case  6: break;                          //CCR3 not used
            case  8: break;                          //CCR4 not used
            case 10: break;                          //CCR5 not used
            case 12: break;                          //CCR6 not used
            case 14:
                break;
            default: break;
    }





}*/
