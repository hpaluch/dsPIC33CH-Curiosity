/**
  @File Name
    RGB_SW.X/main.c

  @Summary
    Simple RGB LED + Switches demo for dsPIC33CH Curiosity board
    Press S1 to turn-on RED, S2 to GREEN and S3 to BLUE of RGB LED
    or combination of S1, S3, S3
 
    Additionally LED1 and LED2 are blinking using TMR1 to show that CPU
    is alive.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33CH512MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70 (used: v2.00)
        MPLAB 	          :  MPLAB X v5.50
*/

/*
    Modified by Henryk Paluch. Based on:
 
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


static void TMR1_CallBack(void)
{
    LED1_Toggle();
    LED2_Toggle();
}

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    LED1_SetHigh();
    LED2_SetLow();
    TMR1_SetInterruptHandler(&TMR1_CallBack);
    while (1)
    {
        // NOTE: Switches are active in 0! (negative logic)
        if (!S1_GetValue()){
            RGB_RED_SetHigh();
        } else {
            RGB_RED_SetLow();
        }
        
        if (!S2_GetValue()){
            RGB_GREEN_SetHigh();
        } else {
            RGB_GREEN_SetLow();
        }
        
        if (!S3_GetValue()){
            RGB_BLUE_SetHigh();
        } else {
            RGB_BLUE_SetLow();
        }
    }
    /* never returns */
    return 1; 
}
