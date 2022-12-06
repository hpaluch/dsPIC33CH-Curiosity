# dsPIC33CH Curiosity demos

Various demo projects for dsPIC33CH Curiosity board

Hardware Requirements:
- [dsPIC33CH Curiosity Development Board](https://www.microchip.com/en-us/development-tool/DM330028-2)
- Micro USB cable (there is no one included with board!)
- ensure that you downloaded data-sheet from:
  - https://ww1.microchip.com/downloads/en/DeviceDoc/DS50002801%20-%20dsPIC33CH%20Curiosity%20Development%20Board%20Users%20Guide.pdf
- Notice dsPIC type from data-sheet:
  - [dsPIC33CH512MP508](https://www.microchip.com/en-us/product/dsPIC33CH512MP508)


Software Requirements:
- MPLAB X IDE `v5.50`
  > WARNING! Version v6.05 freezes right when Slave project is added to Master!
  > From that point even killing it and running again will not help - it will freeze again!
- DFP: `dsPIC33CH-MP_DFP v1.7.194`
- XC16 `v.20`

# Curiosity board Notes

Please note that you when you create new project you need to select:
- Family: `16-bit DSCs (dsPIC33)`
- Device: `dsPIC33CH512MP508` for Master Core. If you will create also Slave
  project you have to select same CPU with `S1` (Slave) suffix
- Tool: `Starter Kits (PKOB)-SN:BURxxx` (you need to have your Curiosity board 

Here is brief overview of I/O peripherals on Curiosity board - excluding DC/DC converter parts:

| Peripheral | dsPIC33CH pin and/or port |
| --- | --- |
| S1 push-button | RE7 |
| S2 push-button | RE8 |
| S3 push-button | RE9 |
| S4 push-button | /MCLR (reset) |
| R/G/B LED | RB14/RD7/RD5 |
| LED1 red | RE0 |
| LED2 red | RE1 |
| 10kOhm pot | RA0 |

NOTE: To Debug Master core on Curiosity board (with on-board Programmer/Debugger)
you have to make following adjustment in MCC Tool:
- System Module -> Easy Setup -> ICD -> `Communicate on PGC2 and PGD2`

# Project list

* [RGB_SW.X/](RGB_SW.X) - RGB LED switches demo - press S1, S2, S3 to turn on RGB LED - RED, GREEN or
  BLUE channel. Additionally LED1 and LED2 are blinking to show that program is alive. Uses Master core only.
  - used components:
    - TMR1 (Timer1 module), period 250 ms - for blinkings LED1 and LED2 - complementary
    - 3 GPIO Inputs: S1, S2, S3 (on-board switches)
    - 5 GPIO Outputs: LED1, LED2, RGB LED
* [ADC_PWM.X](ADC_PWM.X) - project goal: read potentiometer value using ADC, output variable
  brightness to LED1 and LED2 using PWM
  - used components
    - TMR1 (Timer1 module), period 250 ms - for blinkings LED1 and LED2 - in sync
    - ADC1 Input - to read Potentiometer value
    - PWM1 Output to RB14 Blue LED (and RB15 but that is unused)
    - UART1 Output to PC, 9600Baud, 8-bit,1-stop, no-parity
  - now seems to work


