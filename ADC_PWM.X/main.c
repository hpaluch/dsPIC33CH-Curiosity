/**
  @File Name
    main.c

  @Summary
    ADC and PWM demo - set brightness of RGB Blue LED 
    using PWM based on potentiometer value read with ADC

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
    (c) Henryk Paluch, based on:
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
#include <inttypes.h>


static volatile uint32_t jiffies = 0;
static volatile uint16_t counter = 0;
static void TMR1_CallBack(void)
{
    LED1_Toggle();
    LED2_Toggle();
    counter++;
    jiffies++;
}

static const ADC1_CHANNEL channel = channel_AN0;

// ADC is 12-bit
static const uint16_t MAX_ADC = 0xFFF;
// need to read from MPER (Master Period), assigned in pwm.c
// normally 7999 DEC (8MHz -> 1Khz divider), 0x1f3f HEX
static uint16_t max_duty = 0;

static const int APP_VERSION = 102;

int main(void)
{
    uint16_t pwm_duty_old = 0;
    uint32_t tmp = 0;
    // initialize the device
    SYSTEM_Initialize();
    printf("1.Init\r\n");
    printf("Version: %d.%02d\r\n",APP_VERSION/100, APP_VERSION%100);
    max_duty = MPER; // 7999 dec for 1kHZ period see pwm.c
    printf("max_duty=%" PRIu16 "\r\n", max_duty);
    LED1_SetHigh();
    LED2_SetHigh();
    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    pwm_duty_old = MDC;
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    TMR1_SetInterruptHandler(&TMR1_CallBack);
    printf("1.Main-Loop\r\n");
    while (1)
    {
        uint16_t pwm_duty = 0;
        uint16_t conversion = 0;
        int i=0;

        // A/D Conversion from potentiometer
        ADC1_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC1_SoftwareTriggerDisable();
        while(!ADC1_IsConversionComplete(channel));
        // conversion has real range from 0 to 0xFFF (12-bit ADC)
        conversion = ADC1_ConversionResultGet(channel);

        // just be sure that conversion does not overflows
        tmp = conversion & MAX_ADC;
        // pwm_duty = conversion * max_duty / MAX_ADC
        tmp = tmp * max_duty / MAX_ADC;
        pwm_duty = (uint16_t)tmp;
        if (pwm_duty != pwm_duty_old){
            PWM_GeneratorDisable(PWM_GENERATOR_1);
            PWM_MasterDutyCycleSet(pwm_duty);
            PWM_GeneratorEnable(PWM_GENERATOR_1);
            pwm_duty_old = pwm_duty;
        }
        // print values but do not flood terminal
        if (counter >= 4){
            printf("Uptime ticks: %" PRIu32 "\r\n", jiffies);
            // dump current value on UART
            printf("  ADC=%" PRIu16 " (0x%" PRIx16 ")\r\n",
                    conversion, conversion);
            printf("  PWM_Duty=%" PRIu16 " (0x%" PRIx16 ")\r\n",
                    pwm_duty, pwm_duty);
            counter = 0;
        }
    }
    return 1; 
}

