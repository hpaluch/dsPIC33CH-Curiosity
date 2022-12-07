/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
   SLAVE main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33CH512MP508S1
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


void WaitForDataFromMaster(void)
{
   //Wait for interrupt from master     
   while(!MASTER_IsInterruptRequested()); 
   MASTER_InterruptRequestAcknowledge(); 
   while(MASTER_IsInterruptRequested()); 
   MASTER_InterruptRequestAcknowledgeComplete();
}

void AckDataFromMaster(void)
{
    //Issue interrupt to master
    MASTER_InterruptRequestGenerate();
    while(!MASTER_IsInterruptRequestAcknowledged());
    MASTER_InterruptRequestComplete();
    while(MASTER_IsInterruptRequestAcknowledged());
}

uint16_t greenDuty = 0;
uint16_t redDuty = 0;

MboxPwmGreen_DATA GreenGet;
MboxPwmRed_DATA RedGet;

/*
                         Main application
 */
int main(void)
{
    // SLAVE Main
    SYSTEM_Initialize();
    while (1)
    {
        uint16_t duty;
        
        WaitForDataFromMaster();
        // returns false if this box is empty
        if(MASTER_MboxPwmGreenRead(&GreenGet)){
            duty = GreenGet.ProtocolA[0];
            if (duty != greenDuty){
                PG8DC = duty;
                PG8STATbits.UPDREQ = 1; // Update request set
                while(PG8STATbits.UPDATE){
                    // NOP
                }
                greenDuty = duty;
            }
            AckDataFromMaster();
            continue;
        }
        if(MASTER_MboxPwmRedRead(&RedGet)){
            duty = RedGet.ProtocolB[0];
            if (duty != greenDuty){
                PG6DC = duty;
                PG6STATbits.UPDREQ = 1; // Update request set
                while(PG6STATbits.UPDATE){
                    // NOP
                }
                redDuty = duty;
            }
            AckDataFromMaster();
            continue;
        }
    }
    return 1; 
}
/**
 End of File
*/

