/**
  PWM Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm.h

  @Summary
    This is the generated header file for the PWM driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for PWM.
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

#ifndef PWM_H
#define PWM_H

/**
 Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Type Definitions
*/

/** PWM Generator Definition
 
 @Summary 
   Defines the PWM generators available for PWM
 
 @Description
   This routine defines the PWM generators that are available for the module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    PWM_GENERATOR_6 =  6,       
    PWM_GENERATOR_8 =  8,       
} PWM_GENERATOR;
        
/** PWM Generator Interrupt Definition
 
 @Summary 
   Defines the PWM generator interrupt available for PWM
 
 @Description
   This routine defines the PWM generator interrupt that are available for the module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    PWM_GENERATOR_INTERRUPT_FAULT =  1,       
    PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT =  2,
    PWM_GENERATOR_INTERRUPT_FEED_FORWARD =  3,
    PWM_GENERATOR_INTERRUPT_SYNC =  4,		
} PWM_GENERATOR_INTERRUPT;

/**
 Section: Interface Routines
*/

/**
  @Summary
    Initializes PWM module.

  @Description
    This routine initializes PWM module, using the given initialization data. 

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterPeriod,masterDutyCycle,masterPhase;

    masterPeriod = 0xFFFF;
    masterDutyCycle = 0xFF;
    masterPhase = 0xF;

    PWM_Initialize();
 
    PWM_GeneratorDisable();

    PWM_MasterPeriodSet(masterPeriod);
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_MasterPhaseSet(masterPhase);
 
    PWM_GeneratorEnable(PWM_GENERATOR_1);

    </code>
*/
void PWM_Initialize (void);

/**
  @Summary
    Enables the specific PWM generator.

  @Description
    This routine is used to enable the specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    </code>
*/
inline static void PWM_GeneratorEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6CONLbits.ON = 1;              
                break;       
        case PWM_GENERATOR_8:
                PG8CONLbits.ON = 1;              
                break;       
        default:break;    
    }     
}

/**
  @Summary
    Disables the specific PWM generator.

  @Description
    This routine is used to disable the specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>
    PWM_GeneratorDisable(PWM_GENERATOR_1);
    </code>
*/
inline static void PWM_GeneratorDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6CONLbits.ON = 0;              
                break;       
        case PWM_GENERATOR_8:
                PG8CONLbits.ON = 0;              
                break;       
        default:break;    
    }    
}

/**
  @Summary
    Enables all the generators of PWM module.

  @Description
    This routine is used to enable all the generators of PWM module.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_Enable();
    </code>
*/
inline static void PWM_Enable()
{
    PG6CONLbits.ON = 1;              
    PG8CONLbits.ON = 1;              
}

/**
  @Summary
    Disables all the generators of PWM module.

  @Description
    This routine is used to disable all the generators of PWM module.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_Disable();
    </code>
*/
inline static void PWM_Disable()
{
    PG6CONLbits.ON = 0;              
    PG8CONLbits.ON = 0;              
}

/**
  @Summary
    Sets the period value in count for the Master Time Base generator.

  @Description
    This routine is used to set the period value in count for the Master Time Base generator.

  @Param
    masterPeriod - Period value in count.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterPeriod;

    masterPeriod = 0xFF;
    
    PWM_MasterPeriodSet(masterPeriod);
    </code>
*/
inline static void PWM_MasterPeriodSet(uint16_t masterPeriod)
{
    MPER = masterPeriod;
}

/**
  @Summary
    Used to set the PWM master duty cycle register.

  @Description
    This routine is used to set the PWM master duty cycle register.

  @Param
    masterDutyCycle - Master Duty Cycle value.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterDutyCycle;

    masterDutyCycle = 0xFF;
    
    PWM_MasterDutyCycleSet(masterDutyCycle);
    </code>
*/
inline static void PWM_MasterDutyCycleSet(uint16_t masterDutyCycle)
{
    MDC = masterDutyCycle;
}

/**
  @Summary
    Sets the phase value in count for the Master Time Base generator.

  @Description
    This routine is used to set the phase value in count for the Master Time Base generator.

  @Param
    masterPhase - Phase value in count.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterPhase;

    masterPhase = 0xFF;
    
    PWM_MasterPhaseSet(masterPhase);
    </code>
*/
inline static void PWM_MasterPhaseSet(uint16_t masterPhase)
{
    MPHASE = masterPhase;
}

/**
  @Summary
    Sets the period value in count for the PWM generator specific Time Base.

  @Description
    This routine is used to set the period value in count for the PWM generator specific Time Base.

  @Param
    genNum - PWM generator number.
    period - PWM generator period value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t period;
    
    period = 0xFFFF;
    PWM_PeriodSet(PWM_GENERATOR_1, period);
    </code>
*/
inline static void PWM_PeriodSet(PWM_GENERATOR genNum,uint16_t period)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6PER = period;              
                break;       
        case PWM_GENERATOR_8:
                PG8PER = period;              
                break;       
        default:break;    
    }   
}

/**
  @Summary
    Used to set the PWM generator specific duty cycle register.

  @Description
    This routine is used to set the PWM generator specific duty cycle register.

  @Param
    genNum      - PWM generator number.
    dutyCycle   - PWM generator duty cycle.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t dutyCyle;
    
    dutyCycle = 0xFF;
    PWM_DutyCycleSet(PWM_GENERATOR_1, dutyCycle);
    </code>
*/
inline static void PWM_DutyCycleSet(PWM_GENERATOR genNum,uint16_t dutyCycle)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6DC = dutyCycle;              
                break;       
        case PWM_GENERATOR_8:
                PG8DC = dutyCycle;              
                break;       
        default:break;    
    }  
}

/**
  @Summary
    Sets the phase value in count for the PWM generator specific Time Base.

  @Description
    This routine is used to set the phase value in count for the PWM generator specific Time Base.

  @Param
    genNum - PWM generator number.
    phase - PWM generator phase value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t phase;
    
    phase = 0xFFFF;
    PWM_PhaseSet(PWM_GENERATOR_1, phase);
    </code>
*/
inline static void PWM_PhaseSet(PWM_GENERATOR genNum,uint16_t phase)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6PHASE = phase;              
                break;       
        case PWM_GENERATOR_8:
                PG8PHASE = phase;              
                break;       
        default:break;    
    } 
}

/**
  @Summary
    Updates PWM override data bits with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM override data bits with the requested 
    value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    overrideData    - Override data

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t overrideData;

    overrideData = 0x01;
    
    PWM_OverrideDataSet(PWM_GENERATOR_1, overrideData);
    </code>
*/  
inline static void PWM_OverrideDataSet(PWM_GENERATOR genNum,uint16_t overrideData)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRDAT = overrideData;              
                break;       
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRDAT = overrideData;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Updates PWM override high data bit with the requested value for a specific PWM generator.

  @Description
    This routine is used to update PWM override high data bit with the requested 
    value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum              - PWM generator number.
    overrideDataHigh    - Override data

  @Returns
    None
 
  @Example 
    <code>    
    bool overrideDataHigh;

    overrideDataHigh = true;
    
    PWM_OverrideDataHighSet(PWM_GENERATOR_1, overrideDataHigh);
    </code>
*/  
inline static void PWM_OverrideDataHighSet(PWM_GENERATOR genNum,bool overrideDataHigh)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRDAT |= (overrideDataHigh << 1);
                break;
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRDAT |= (overrideDataHigh << 1);
                break;
        default:break;    
    }
}

/**
  @Summary
    Updates PWM override low data bit with the requested value for a specific PWM generator.

  @Description
    This routine is used to update PWM override low data bit with the requested 
    value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum             - PWM generator number.
    overrideDataLow    - Override data

  @Returns
    None
 
  @Example 
    <code>    
    bool overrideDataLow;

    overrideDataLow = true;
    
    PWM_OverrideDataLowSet(PWM_GENERATOR_1, overrideDataLow);
    </code>
*/  
inline static void PWM_OverrideDataLowSet(PWM_GENERATOR genNum,bool overrideDataLow)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRDAT |= overrideDataLow;             
                break;  
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRDAT |= overrideDataLow;             
                break;  
        default:break;    
    }
}

/**
  @Summary
    Gets PWM override value for the PWM Generator.

  @Description
    This routine is used to get PWM override value for the PWM Generator 
    selected by the argument PWM_GENERATOR.
	
  @Param
    genNum          - PWM generator number.

  @Returns
    Override data for the PWM Generator selected by the argument PWM_GENERATOR.
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t overrideData;
    
    genNum = PWM_GENERATOR_1;
    overrideData = PWM_OverrideDataGet(genNum, overrideData);
    </code>
*/
inline static uint16_t PWM_OverrideDataGet(PWM_GENERATOR genNum)
{
    uint16_t overrideData;
    switch(genNum) { 
        case PWM_GENERATOR_6:
                overrideData = PG6IOCONLbits.OVRDAT;             
                break;
        case PWM_GENERATOR_8:
                overrideData = PG8IOCONLbits.OVRDAT;             
                break;
        default:break;    
    }
    return overrideData;
}

/**
  @Summary
    Enables PWM override on PWMH output for specific PWM generator.

  @Description
    This routine is used to enables PWM override on PWMH output for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideHighEnable(PWM_GENERATOR_1);
    </code>
*/  
inline static void PWM_OverrideHighEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRENH = 1;              
                break;
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRENH = 1;              
                break;
        default:break;    
    }
}

/**
  @Summary
    Enables PWM override on PWML output for specific PWM generator.

  @Description
    This routine is used to enables PWM override on PWML output for specific PWM generator
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideLowEnable(PWM_GENERATOR_1);
    </code>
*/  
inline static void PWM_OverrideLowEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRENL = 1;              
                break; 
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRENL = 1;              
                break; 
        default:break;    
    }
}

/**
  @Summary
    Disables PWM override on PWMH output for specific PWM generator.

  @Description
    This routine is used to disable PWM override on PWMH output for specific PWM generator 
    selected by the argument PWM_GENERATOR.


  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideHighDisable(PWM_GENERATOR_1);
    </code>
*/  
inline static void PWM_OverrideHighDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRENH = 0;              
                break;
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRENH = 0;              
                break;
        default:break;    
    }
}

/**
  @Summary
    Disables PWM override on PWML output for specific PWM generator.

  @Description
    This routine is used to disable PWM override on PWML output for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideLowDisable(PWM_GENERATOR_1);
    </code>
*/  
inline static void PWM_OverrideLowDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRENL = 0;              
                break;   
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRENL = 0;              
                break;   
        default:break;    
    }
}

/**
  @Summary
    Updates PWM Deadtime low register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime low register with the requested
    value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum      - PWM generator number.
    deadtimeLow - Deadtime low value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtimeLow;

    deadtimeLow = 0x01;
    
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, deadtimeLow);
    </code>
*/  
inline static void PWM_DeadTimeLowSet(PWM_GENERATOR genNum,uint16_t deadtimeLow)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6DTL = deadtimeLow;              
                break;       
        case PWM_GENERATOR_8:
                PG8DTL = deadtimeLow;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Updates PWM Deadtime high register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime high register with the requested
    value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    deadtimeHigh    - Deadtime high value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtimeHigh;

    deadtimeHigh = 0x01;
    
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, deadtimeHigh);
    </code>
*/  
inline static void PWM_DeadTimeHighSet(PWM_GENERATOR genNum,uint16_t deadtimeHigh)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6DTH = deadtimeHigh;              
                break;       
        case PWM_GENERATOR_8:
                PG8DTH = deadtimeHigh;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Updates PWM Deadtime low and high register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime low and high register with the 
    requested value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    deadtimeHigh    - Deadtime value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtime;

    deadtime = 0x01;
    
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, deadtime);
    </code>
*/  
inline static void PWM_DeadTimeSet(PWM_GENERATOR genNum,uint16_t deadtime)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6DTL = deadtime;
                PG6DTH = deadtime; 				
                break;       
        case PWM_GENERATOR_8:
                PG8DTL = deadtime;
                PG8DTH = deadtime; 				
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the PWM trigger compare value in count for the 
    PWM Generator.

  @Description
    This routine is used to set the PWM trigger compare value in count
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    trigCompValue   - Trigger compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t trigCompValue;

    trigCompValue = 0x01;
    
    genNum = PWM_GENERATOR_1;
    PWM_TriggerCompareValueSet(genNum, trigCompValue);
    </code>
*/  
inline static void PWM_TriggerCompareValueSet(PWM_GENERATOR genNum,uint16_t trigCompValue)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6TRIGA = trigCompValue;              
                break;      
        case PWM_GENERATOR_8:
                PG8TRIGA = trigCompValue;              
                break;      
        default:break;    
    }
}

/**
  @Summary
    Enables interrupt requests for the PWM Generator.

  @Description
    This routine is used to enable interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    PWM_GeneratorInterruptEnable(genNum, interrupt);
    </code>
*/ 
inline static void PWM_GeneratorInterruptEnable(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        PG6EVTHbits.FLTIEN = true;               
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        PG6EVTHbits.CLIEN = true;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        PG6EVTHbits.FFIEN = true;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        PG6EVTHbits.SIEN = true;
                                        break;														
                        default:break;  
                }              
                break;   
        case PWM_GENERATOR_8:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        PG8EVTHbits.FLTIEN = true;               
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        PG8EVTHbits.CLIEN = true;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        PG8EVTHbits.FFIEN = true;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        PG8EVTHbits.SIEN = true;
                                        break;														
                        default:break;  
                }              
                break;   
        default:break;  
    }
}

/**
  @Summary
    Disables interrupt requests for the PWM Generator.

  @Description
    This routine is used to disables interrupt requests for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    PWM_GeneratorInterruptDisable(genNum, interrupt);
    </code>
*/ 
inline static void PWM_GeneratorInterruptDisable(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        PG6EVTHbits.FLTIEN = false;               
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        PG6EVTHbits.CLIEN = false;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        PG6EVTHbits.FFIEN = false;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        PG6EVTHbits.SIEN = false;
                                        break;								
                        default:break;  
                }              
                break;  
        case PWM_GENERATOR_8:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        PG8EVTHbits.FLTIEN = false;               
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        PG8EVTHbits.CLIEN = false;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        PG8EVTHbits.FFIEN = false;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        PG8EVTHbits.SIEN = false;
                                        break;								
                        default:break;  
                }              
                break;  
        default:break;  
    }
}

/**
  @Summary
    Clears PWM interrupt status for the PWM Generator.

  @Description
    This routine is used to clear PWM interrupt status for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    PWM_GeneratorEventStatusClear(genNum, interrupt);
    </code>
*/
inline static void PWM_GeneratorEventStatusClear(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        PG6STATbits.FLTEVT = 0;							
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        PG6STATbits.CLEVT = 0;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        PG6STATbits.FFEVT = 0;
                                        break;	
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        PG6STATbits.SEVT = 0;
                                        break;							
                        default:break;  
                }              
                break; 
        case PWM_GENERATOR_8:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        PG8STATbits.FLTEVT = 0;							
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        PG8STATbits.CLEVT = 0;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        PG8STATbits.FFEVT = 0;
                                        break;	
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        PG8STATbits.SEVT = 0;
                                        break;							
                        default:break;  
                }              
                break; 
        default:break;  
    }
}

/**
  @Summary
    Gets PWM interrupt status for the PWM Generator.

  @Description
    This routine is used to get PWM interrupt status for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    true - Interrupt is pending.
    false - Interrupt is not pending.
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    bool status;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    status = PWM_GeneratorEventStatusGet(genNum, interrupt);
    </code>
*/
inline static bool PWM_GeneratorEventStatusGet(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    bool status = false;
    switch(genNum) { 
        case PWM_GENERATOR_6:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        status = PG6STATbits.FLTEVT;               
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        status = PG6STATbits.CLEVT;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        status = PG6STATbits.FFEVT;
                                        break;	
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        status = PG6STATbits.SEVT;
                                        break;							
                        default:break;  
                }              
                break; 
        case PWM_GENERATOR_8:
                switch(interrupt) { 
                        case PWM_GENERATOR_INTERRUPT_FAULT:
                                        status = PG8STATbits.FLTEVT;               
                                        break;       
                        case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
                                        status = PG8STATbits.CLEVT;
                                        break;
                        case PWM_GENERATOR_INTERRUPT_FEED_FORWARD:
                                        status = PG8STATbits.FFEVT;
                                        break;	
                        case PWM_GENERATOR_INTERRUPT_SYNC:
                                        status = PG8STATbits.SEVT;
                                        break;							
                        default:break;  
                }              
                break; 
        default:break;  
    }
	return status;
}

/**
  @Summary
    Sets the TRIGA compare value in count for a specific PWM generator.

  @Description
    This routine is used to set the TRIGA compare value in count for a specific PWM generator
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    trigA  - TRIGA compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t trigA;
    
    trigA = 0xF;
    PWM_TriggerACompareValueSet(PWM_GENERATOR_1, trigA);
    </code>
*/
inline static void PWM_TriggerACompareValueSet(PWM_GENERATOR genNum,uint16_t trigA)
{ 
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6TRIGA = trigA;              
                break;       
        case PWM_GENERATOR_8:
                PG8TRIGA = trigA;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the TRIGB compare value in count for a specific PWM generator.

  @Description
    This routine is used to set the TRIGB compare value in count for a specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    trigB  - TRIGB compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t trigB;
    
    trigB = 0xF;
    PWM_TriggerBCompareValueSet(PWM_GENERATOR_1, trigB);
    </code>
*/
inline static void PWM_TriggerBCompareValueSet(PWM_GENERATOR genNum,uint16_t trigB)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6TRIGB = trigB;              
                break;       
        case PWM_GENERATOR_8:
                PG8TRIGB = trigB;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the TRIGC compare value in count for a specific PWM generator.

  @Description
    This routine is used to set the TRIGC compare value in count for a specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    trigC  - TRIGC compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t trigC;
    
    trigC = 0xF;
    PWM_TriggerCCompareValueSet(PWM_GENERATOR_1, trigC);
    </code>
*/
inline static void PWM_TriggerCCompareValueSet(PWM_GENERATOR genNum,uint16_t trigC)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6TRIGC = trigC;              
                break;       
        case PWM_GENERATOR_8:
                PG8TRIGC = trigC;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Requests to update the data registers for specific PWM generator.

  @Description
    This routine is used to request to update the data registers for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_SoftwareUpdateRequest(PWM_GENERATOR_1);
    </code>
*/  
inline static void PWM_SoftwareUpdateRequest(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6STATbits.UPDREQ = 1;              
                break;       
        case PWM_GENERATOR_8:
                PG8STATbits.UPDREQ = 1;              
                break;       
        default:break;    
    }

}

/**
  @Summary
    Gets the status of the update request for specific PWM generator.

  @Description
    This routine is used to get the status of the update request for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    bool status;
    
    status = PWM_SoftwareUpdatePending(PWM_GENERATOR_1);
    </code>
*/  
inline static bool PWM_SoftwareUpdatePending(PWM_GENERATOR genNum)
{
    bool status = false;
    switch(genNum) { 
        case PWM_GENERATOR_6:
                status = PG6STATbits.UPDATE;              
                break;       
        case PWM_GENERATOR_8:
                status = PG8STATbits.UPDATE;              
                break;       
        default:break;   
    }
    return status;
}

/**
  @Summary
    Clears the status of PWM latched fault mode for the PWM Generator.

  @Description
    This routine is used to clear the status of PWM latched fault mode 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_FaultModeLatchClear(genNum);
    </code>
*/  
inline static void PWM_FaultModeLatchClear(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6: 
                PG6FPCILbits.SWTERM = 1;
                break;   
        case PWM_GENERATOR_8: 
                PG8FPCILbits.SWTERM = 1;
                break;   
        default:break;   
    }   
}

/**
  @Summary
    Callback for PWM6 interrupt.

  @Description
    This routine is callback for PWM6 interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_Generator6_CallBack();
    </code>
*/
void PWM_Generator6_CallBack(void);

/**
  @Summary
    Tasks routine for PWM6.

  @Description
    This is a tasks routine for PWM6.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_Generator6_Tasks();
    </code>
*/
void PWM_Generator6_Tasks(void);

/**
  @Summary
    Callback for PWM8 interrupt.

  @Description
    This routine is callback for PWM8 interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_Generator8_CallBack();
    </code>
*/
void PWM_Generator8_CallBack(void);

/**
  @Summary
    Tasks routine for PWM8.

  @Description
    This is a tasks routine for PWM8.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_Generator8_Tasks();
    </code>
*/
void PWM_Generator8_Tasks(void);


/**
  @Summary
    Callback for EventA interrupt.

  @Description
    This routine is callback for EventA interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventA_CallBack();
    </code>
*/
void PWM_EventA_CallBack(void);

/**
  @Summary
    Tasks routine for EventA.

  @Description
    This is a tasks routine for EventA.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventA_Tasks();
    </code>
*/
void PWM_EventA_Tasks(void);

/**
  @Summary
    Callback for EventB interrupt.

  @Description
    This routine is callback for EventB interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventB_CallBack();
    </code>
*/
void PWM_EventB_CallBack(void);

/**
  @Summary
    Tasks routine for EventB.

  @Description
    This is a tasks routine for EventB.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventB_Tasks();
    </code>
*/
void PWM_EventB_Tasks(void);

/**
  @Summary
    Callback for EventC interrupt.

  @Description
    This routine is callback for EventC interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventC_CallBack();
    </code>
*/
void PWM_EventC_CallBack(void);

/**
  @Summary
    Tasks routine for EventC.

  @Description
    This is a tasks routine for EventC.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventC_Tasks();
    </code>
*/
void PWM_EventC_Tasks(void);

/**
  @Summary
    Callback for EventD interrupt.

  @Description
    This routine is callback for EventD interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventD_CallBack();
    </code>
*/
void PWM_EventD_CallBack(void);

/**
  @Summary
    Tasks routine for EventD.

  @Description
    This is a tasks routine for EventD.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventD_Tasks();
    </code>
*/
void PWM_EventD_Tasks(void);

/**
  @Summary
    Callback for EventE interrupt.

  @Description
    This routine is callback for EventE interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventE_CallBack();
    </code>
*/
void PWM_EventE_CallBack(void);

/**
  @Summary
    Tasks routine for EventE.

  @Description
    This is a tasks routine for EventE.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventE_Tasks();
    </code>
*/
void PWM_EventE_Tasks(void);

/**
  @Summary
    Callback for EventF interrupt.

  @Description
    This routine is callback for EventF interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventF_CallBack();
    </code>
*/
void PWM_EventF_CallBack(void);

/**
  @Summary
    Tasks routine for EventF.

  @Description
    This is a tasks routine for EventF.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    <code>    
    PWM_EventF_Tasks();
    </code>
*/
void PWM_EventF_Tasks(void);


/*******************************************************************************

  !!! Deprecated Definitions and APIs !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/
/**
  @Summary
    Enables the specific PWM generator.

  @Description
    This routine is used to enable the specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_ModuleEnable(genNum);
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorEnable instead."))) PWM_ModuleEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6CONLbits.ON = 1;              
                break;       
        case PWM_GENERATOR_8:
                PG8CONLbits.ON = 1;              
                break;       
        default:break;    
    }     
}

/**
  @Summary
    Disables the specific PWM generator.

  @Description
    This routine is used to disable the specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_ModuleDisable(genNum);
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorDisable instead."))) PWM_ModuleDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6CONLbits.ON = 0;              
                break;       
        case PWM_GENERATOR_8:
                PG8CONLbits.ON = 0;              
                break;       
        default:break;    
    }    
}

/**
  @Summary
    Enables/Disables PWM override on PWML output for specific PWM generator.

  @Description
    This routine is used to enable/disable PWM override on PWML output for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    enableOverride  - Data to enable or disable override low. 

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideLowEnableSet(PWM_GENERATOR_1, enableOverride);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_OverrideLowEnable and PWM_OverrideLowDisable instead."))) PWM_OverrideLowEnableSet(PWM_GENERATOR genNum, bool enableOverride)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRENL = enableOverride;              
                break;       
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRENL = enableOverride;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Enables/Disables PWM override on PWMH output for specific PWM generator.

  @Description
    This routine is used to enable/disable PWM override on PWMH output for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    enableOverride  - Data to enable or disable override high. 

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideHighEnableSet(PWM_GENERATOR_1, enableOverride);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_OverrideHighEnable and PWM_OverrideHighDisable instead."))) PWM_OverrideHighEnableSet(PWM_GENERATOR genNum, bool enableOverride)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6IOCONLbits.OVRENH = enableOverride;              
                break;       
        case PWM_GENERATOR_8:
                PG8IOCONLbits.OVRENH = enableOverride;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the TRIGA compare value in count for a specific PWM generator.

  @Description
    This routine is used to set the TRIGA compare value in count for a specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    trigA  - TRIGA compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t trigA;
    
    trigA = 0xF;
    PWM_TRIGACompareSet(PWM_GENERATOR_1, trigA);
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_TriggerACompareValueSet instead."))) PWM_TRIGACompareSet(PWM_GENERATOR genNum,uint16_t trigA)
{ 
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6TRIGA = trigA;              
                break;       
        case PWM_GENERATOR_8:
                PG8TRIGA = trigA;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the TRIGB compare value in count for a specific PWM generator.

  @Description
    This routine is used to set the TRIGB compare value in count for a specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    trigB  - TRIGB compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t trigB;
    
    trigB = 0xF;
    PWM_TRIGBCompareSet(PWM_GENERATOR_1, trigB);
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_TriggerBCompareValueSet instead."))) PWM_TRIGBCompareSet(PWM_GENERATOR genNum,uint16_t trigB)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6TRIGB = trigB;              
                break;       
        case PWM_GENERATOR_8:
                PG8TRIGB = trigB;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the TRIGC compare value in count for a specific PWM generator.

  @Description
    This routine is used to set the TRIGC compare value in count for a specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    trigC  - TRIGC compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t trigC;
    
    trigC = 0xF;
    PWM_TRIGCCompareSet(PWM_GENERATOR_1, trigC);
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_TriggerCCompareValueSet instead."))) PWM_TRIGCCompareSet(PWM_GENERATOR genNum,uint16_t trigC)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6TRIGC = trigC;              
                break;       
        case PWM_GENERATOR_8:
                PG8TRIGC = trigC;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Requests to update the data registers for specific PWM generator.

  @Description
    This routine is used to request to update the data registers for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_DataUpdateRequestSet(PWM_GENERATOR_1);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_SoftwareUpdateRequest instead."))) PWM_DataUpdateRequestSet(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_6:
                PG6STATbits.UPDREQ = 1;              
                break;       
        case PWM_GENERATOR_8:
                PG8STATbits.UPDREQ = 1;              
                break;       
        default:break;    
    }

}

/**
  @Summary
    Gets the status of the update request for specific PWM generator.

  @Description
    This routine is used to get the status of the update request for specific PWM generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    bool status;
    
    status = PWM_DataUpdateStatusGet(PWM_GENERATOR_1);
    </code>
*/  
inline static bool __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_SoftwareUpdatePending instead."))) PWM_DataUpdateStatusGet(PWM_GENERATOR genNum)
{
    bool status = false;
    switch(genNum) { 
        case PWM_GENERATOR_6:
                status = PG6STATbits.UPDATE;              
                break;       
        case PWM_GENERATOR_8:
                status = PG8STATbits.UPDATE;              
                break;       
        default:break;   
    }
    return status;
}

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //PWM_H
