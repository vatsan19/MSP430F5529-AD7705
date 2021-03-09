/*****************************************************************
Module name: Implementation of clock_and_timer

Copyright 2020-NTU/KVI
All Rights Reserved

The information contained herein is confidential property of KVI and NTU.
The use, copying, transfer or disclosure of such information is
prohibited except by express written agreement with Company.

Description: This is the implementation of the module clock and timer. It has
definitions for clock and timer config

*******************************************************************/
/* Include section
Add all #includes here
*******************************************************************/
#include "driverlib.h"
#include "Clock_and_timer.h"

/*******************************************************************
Function definitions
*******************************************************************/
void clock_and_timer_config(uint16_t ADC_sampling_freq,uint16_t UART_sending_freq)
{
    /*
     * Clock configuration is skipped and a default configuration is assumed
     * We have MCLK <- DCO,FLL <- 8MHz
     * We have SMCLK<- DCO,FLL <- 8MHz
     * We have ACLK <- REFO    <- 32kHz
     * We have USBCLK<- XT1    <- 4MHz
     */

    /***************************************************************************************************************
     * Timer configuration
     */
    //clear interrupts for 3 capture compare registers


    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3);


    //Timer sourced by SMCLK, starts in up-mode
    Timer_A_initUpModeParam initUpModeParam = {0};
    initUpModeParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    initUpModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    initUpModeParam.timerPeriod = 0x8192;
    initUpModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initUpModeParam.captureCompareInterruptEnable_CCR0_CCIE =
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initUpModeParam.timerClear = TIMER_A_SKIP_CLEAR;
    initUpModeParam.startTimer = true;
    Timer_A_initUpMode(TIMER_A0_BASE, &initUpModeParam);


    //Initialize compare mode to generate signal for ADC
    Timer_A_initCompareModeParam initComp1Param = {0};
    initComp1Param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    initComp1Param.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initComp1Param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    initComp1Param.compareValue = SMCLKFREQPRE/(ADC_sampling_freq);
    Timer_A_initCompareMode(TIMER_A0_BASE, &initComp1Param);

    //For DMA0 trigger
    Timer_A_initCompareModeParam initCompareModeParam = {0};
    initCompareModeParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    initCompareModeParam.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initCompareModeParam.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    initCompareModeParam.compareValue = 1;
    Timer_A_initCompareMode(TIMER_A0_BASE, &initCompareModeParam);

    //Initialize compare mode to generate signal for UART2

    initComp1Param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    initComp1Param.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initComp1Param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    initComp1Param.compareValue = SMCLKFREQPRE/(8*UART_sending_freq);
    Timer_A_initCompareMode(TIMER_A0_BASE, &initComp1Param);
}

void timer_start_counter(uint16_t base_address,uint16_t timer_mode)
{
    Timer_A_startCounter(base_address, timer_mode);
    Timer_A_enableCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE);
    Timer_A_enableInterrupt(TIMER_A0_BASE);
}
