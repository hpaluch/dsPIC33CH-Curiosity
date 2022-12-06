/**
  MASTER Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    master.c

  @Summary
    This is the generated driver implementation file for the MASTER driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for MASTER.
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

#include <xc.h>
#include "master.h"

inline static bool MASTER_MboxPwmGreenIsFull();
inline static bool MASTER_MboxPwmGreenIsEmpty();
inline static bool MASTER_MboxPwmRedIsFull();
inline static bool MASTER_MboxPwmRedIsEmpty();


/**
 Section: Driver Interface Function Definitions
*/

void MASTER_Initialize()
{
    //RFITSEL Trigger data valid interrupt when 1st FIFO entry is written by Slave; MTSIACK disabled; STMIRQ disabled; MRSTIE disabled; 
    SI1CON = 0x00;	


}

void MASTER_InterruptRequestGenerate()
{
    SI1CONbits.STMIRQ = 1;
}

bool MASTER_IsInterruptRequestAcknowledged()
{
    return(SI1STATbits.STMIACK);
    
}

void MASTER_InterruptRequestComplete()
{
    SI1CONbits.STMIRQ = 0;
}
 
bool MASTER_IsInterruptRequested()
{
    return(SI1STATbits.MTSIRQ);
}
void MASTER_InterruptRequestAcknowledge()
{
    SI1CONbits.MTSIACK = 1;
}

void MASTER_InterruptRequestAcknowledgeComplete()
{
    SI1CONbits.MTSIACK = 0;
}
 
MASTER_SYSTEM_STATUS MASTER_SystemStatusGet()
{
    MASTER_SYSTEM_STATUS systemStatus = MASTER_SYSTEM_STATUS_RUNNING;
    
    
    if(SI1STATbits.MSTRST)
    {
        systemStatus = MASTER_SYSTEM_STATUS_IN_RESET;
    }
    else
    {
        switch(SI1STATbits.MSTPWR)
        {
            case 0: systemStatus = MASTER_SYSTEM_STATUS_NOT_IN_LOW_POWER_MODE;
                    break;
            case 1: systemStatus = MASTER_SYSTEM_STATUS_IDLE;
                    break;
            case 2: systemStatus = MASTER_SYSTEM_STATUS_SLEEP;
                    break;
            default:systemStatus = MASTER_SYSTEM_STATUS_RUNNING;
                    break;             
        }
    }
    return systemStatus;
}

uint16_t MASTER_Read(uint16_t *pData, uint16_t wordCount)
{
    uint16_t readCountStatus = 0;
    
    while(wordCount)
    {
        if(SI1FIFOCSbits.SRFEMPTY != 1)
        {
            *pData++ = SRMWFDATA;
            wordCount--;
            readCountStatus++;
        }
        else
        {
            break;
        }
    }
    return readCountStatus;  
}

uint16_t MASTER_Write(uint16_t *pData, uint16_t wordCount)
{
    uint16_t writeCountStatus = 0;
    
    while(wordCount)
    {
        if(SI1FIFOCSbits.SWFFULL != 1)
        {
            SWMRFDATA = *pData++;
            wordCount--;
            writeCountStatus++;
        }
        else
        {
            break;
        }
    }
    return writeCountStatus;
}
 
bool MASTER_MboxPwmGreenRead(MboxPwmGreen_DATA *pData)
{
    bool status = false;    
    if(MASTER_MboxPwmGreenIsFull())
    {
        pData->ProtocolA[0] = SI1MBX0D;

        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}


inline static bool MASTER_MboxPwmGreenIsFull()
{
    return (SI1MBXSbits.DTRDYA);
}

inline static bool MASTER_MboxPwmGreenIsEmpty()
{
    return (!SI1MBXSbits.DTRDYA);
}
bool MASTER_MboxPwmRedRead(MboxPwmRed_DATA *pData)
{
    bool status = false;    
    if(MASTER_MboxPwmRedIsFull())
    {
        pData->ProtocolB[0] = SI1MBX1D;

        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}


inline static bool MASTER_MboxPwmRedIsFull()
{
    return (SI1MBXSbits.DTRDYB);
}

inline static bool MASTER_MboxPwmRedIsEmpty()
{
    return (!SI1MBXSbits.DTRDYB);
}







