/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    MASTER main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

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

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"

volatile uint16_t jiffies = 0;
// Reserved Timer callback name - see tmr1.c
void TMR1_CallBack(void)
{
    // called every 10ms
    jiffies++;
}

void my_msleep(uint16_t ms)
{
    uint16_t ticks;
    uint16_t target_jiffies;
    
    ticks = ms / 10;
    if (ticks == 0){
        ticks = 1;
    }
    target_jiffies = jiffies + ticks;
    // TODO: Handle properly overflow
    while(jiffies < target_jiffies || jiffies != target_jiffies){
        // NOP
    }
}

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
     //Program and enable slave 
    SLAVE1_Program(); 
    SLAVE1_Start(); 
      
    TMR1_Start();
    LED1_SetHigh();
    LED2_SetHigh();
    // blink LED1 & LED2 to user for 1s to ack startup
    my_msleep(1000);
    LED1_SetLow();
    LED2_SetLow();    
    while (1)
    {
        // sleep 50 ms
        my_msleep(50);
        if(S1_GetValue()==0 || S2_GetValue()==0){
            LED1_SetHigh();
        } else {
            LED1_SetLow();
        }
        if (S2_GetValue()==0 || S3_GetValue()==0){
            LED2_SetHigh();
        } else {
            LED2_SetLow();
        }
        // handle Blue channel PWM
        if (S3_GetValue()==0){
            // we use global MPER (Master Period), not PG1PER
            PG1DC = (PG1DC + MPER/50) % MPER;
            PG1STATbits.UPDREQ = 1; // Update request set
            while(PG1STATbits.UPDATE){
                // NOP
            }
        }
    }
    return 1; 
}
/**
 End of File
*/

