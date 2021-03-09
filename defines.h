/*
 * defines.h
 *
 *  Created on: 15 Jan 2021
 *      Author: kvist
 */
#include "driverlib.h"

#ifndef DEFINES_H_
#define DEFINES_H_

#define NUMSAMPLES 10
#define NUMBYTE 2
#define UART_PORT GPIO_PORT_P4
#define UART_TRANSMIT_PIN  GPIO_PIN4
#define UART_RECEIVE_PIN  GPIO_PIN5

// LED ports
#define LED1_PORT GPIO_PORT_P1
#define LED1_PIN  GPIO_PIN0

// SPI ports
#define SPI_PORT GPIO_PORT_P3
#define SPI_SIMO_PIN GPIO_PIN0
#define SPI_SOMI_PIN GPIO_PIN1
#define SPI_SCLK_PIN GPIO_PIN2
#define SPI_CS_PORT GPIO_PORT_P2
#define SPI_CS_PIN  GPIO_PIN0
#define RESET_PORT GPIO_PORT_P1
#define RESET_PIN GPIO_PIN5
#define DRDY_PORT GPIO_PORT_P2
#define DRDY_PIN  GPIO_PIN7

#define SMCLKFREQ   8000000
#define SMCLKFREQPRE 125000
#define MCLKFREQ    8000000
#define ACLKFREQ    32000
#define USBCLKFREQ  4000000
#define SMCLKDIV    64
#define SPICLK                          500000

//register selection
//RS2 RS1 RS0
#define REG_CMM  0x0 //communication register 8 bit
#define REG_SETUP  0x1 //setup register 8 bit
#define REG_CLOCK  0x2 //clock register 8 bit
#define REG_DATA  0x3 //data register 16 bit, contains conversion result
#define REG_TEST  0x4 //test register 8 bit, POR 0x0
#define REG_NOP  0x5 //no operation
#define REG_OFFSET  0x6 //offset register 24 bit
#define REG_GAIN  0x7 // gain register 24 bit

//channel selection for AD7706 (for AD7705 use the first two channel definitions)
//CH1 CH0
#define CHN_AIN1  0x0 //AIN1 calibration register pair 0
#define CHN_AIN2  0x1 //AIN2 calibration register pair 1
#define CHN_COMM  0x2 //common calibration register pair 0
#define CHN_AIN3  0x3 //AIN3 calibration register pair 2

//output update rate
//CLK FS1 FS0
#define UPDATE_RATE_20  0x0 // 20 Hz
#define UPDATE_RATE_25  0x1 // 25 Hz
#define UPDATE_RATE_100  0x2 // 100 Hz
#define UPDATE_RATE_200  0x3 // 200 Hz
#define UPDATE_RATE_50  0x4 // 50 Hz
#define UPDATE_RATE_60  0x5 // 60 Hz
#define UPDATE_RATE_250  0x6 // 250 Hz
#define UPDATE_RATE_500  0x7 // 500 Hz

//operating mode options
//MD1 MD0
#define MODE_NORMAL  0x0 //normal mode
#define MODE_SELF_CAL  0x1 //self-calibration
#define MODE_ZERO_SCALE_CAL  0x2 //zero-scale system calibration, POR 0x1F4000, set FSYNC high before calibration, FSYNC low after calibration
#define MODE_FULL_SCALE_CAL  0x3 //full-scale system calibration, POR 0x5761AB, set FSYNC high before calibration, FSYNC low after calibration

//gain setting
#define GAIN_1  0x0
#define GAIN_2  0x1
#define GAIN_4  0x2
#define GAIN_8  0x3
#define GAIN_16  0x4
#define GAIN_32  0x5
#define GAIN_64  0x6
#define GAIN_128  0x7

#define UNIPOLAR  0x0
#define BIPOLAR  0x1

#define CLK_DIV_1  0x1
#define CLK_DIV_2  0x2
#define       SPI_PERIPHERAL    GPIO_PORT_P3,SPI_SCLK_PIN+SPI_SIMO_PIN+SPI_SOMI_PIN
#endif /* DEFINES_H_ */
