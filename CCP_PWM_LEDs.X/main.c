/**
  @Company
    Microchip Technology Inc.

  @File Name
    CCP_PWM_LEDs.X/main.c

  @Summary
     Control brightness of RGB LED on Potentiometer angle
     using SCCP PWM Module

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33CH512MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"

const ADC1_CHANNEL channel = pot_AN0;

uint16_t ReadADC()
{
    int i;
    uint16_t conversion = 0;
    
    // from adc1.h
    ADC1_SoftwareTriggerEnable();
    //Provide Delay
    for(i=0;i <1000;i++)
    {
    }
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel);
    return conversion;
}

const uint16_t initPotValue = 0xff;

int main(void)
{
    uint16_t potValue = initPotValue, oldPotValue=initPotValue;
    // initialize the device
    SYSTEM_Initialize();
    ADC1_Enable();
    ADC1_ChannelSelect(channel);

    // PWM Settings
    CCP1PRL = 0x1001; // period - 1, ADC range is 0xfff
    CCP1RA =  0x0000; // where pulse starts
    CCP1RB =  initPotValue; // where pulse ends
    
    SCCP1_COMPARE_Start();
    
    while (1)
    {
        potValue = ReadADC();
        potValue &= 0xFFF; // ensure that ADC value is 12-bit
        if (potValue != oldPotValue){
            CCP1RB =  potValue; // where pulse ends            
            oldPotValue  = potValue;
        }
    }
    return 1; 
}

