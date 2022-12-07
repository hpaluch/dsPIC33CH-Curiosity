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

For Demos with UART you additionally need:
- 2nd Micro USB cable (not included with Curiosity)
- for Windows < 10 download driver from 
  - https://www.microchip.com/en-us/product/MCP2221A 
  - for example: https://ww1.microchip.com/downloads/en/DeviceDoc/MCP2221_Windows_Driver_2021-02-22.zip

# Curiosity board Notes

Please note that when you create new project you need to select:
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

NOTE: dsPIC33CH has actually two kinds of PWM:

1. High Resolution PWM (special module available on selected PICs only)
1. SCCP PWM (common module available on most PICs)

* [RGB_SW.X/](RGB_SW.X) - RGB LED switches demo - press S1, S2, S3 to turn on RGB LED - RED, GREEN or
  BLUE channel. Additionally LED1 and LED2 are blinking to show that program is alive. Uses Master core only.
  - used components:
    - TMR1 (Timer1 module), period 250 ms - for blinking LED1 and LED2 - complementary
    - 3 GPIO Inputs: S1, S2, S3 (on-board switches)
    - 5 GPIO Outputs: LED1, LED2, RGB LED
* [ADC_PWM.X](ADC_PWM.X)
  - high resolution PWM example
  - ADC + PWM Example: read potentiometer value using ADC and set RGB LED (Blue) brightness
    using PWM
  - additionally LED1 & LED2 are synchronously blinking each second using TMR1 to show
    that board is alive
  - used components
    - `TMR1` (Timer1 module), period 250 ms - for blinking LED1 and LED2 - in sync
    - `ADC1` Input - to read Potentiometer value
    - `PWM1` Output to RB14 Blue LED (and RB15 but that is unused)
    - `UART1` Output to PC, 9600Baud, 8-bit,1-stop, no-parity
  - inputs:
    - potentiometer - value read via ADC and used for PWM duty cycle
  - outputs:
    - RGB LED, Blue channel - brightness via PWM, driven by potentiometer
    - dump current ADC and PWM values on UART every second
      - use 9600 Baud, 8-bit, 1 stop-bit, no-parity, no flow control on your terminal (for example Putty)
  - resources:
    - https://microchipdeveloper.com/projects:16bit-adc
    - https://microchipdeveloper.com/pwr3101:pwm-operations
    - https://www.microchip.com/forums/m1181113.aspx
* [RGB-PWM-MS/RGB_PWM.X](RGB-PWM-MS/RGB_PWM.X)
  - high resolution PWM example
  - control all 3 RGB channels of RGB LED using PWMs, duty adjustable by S1, S2, S3
  - also show state of S1, S2, S3 on LED1 and LED2 (where S2 lights both LED1 and LED2)
  - we have to use both cores because:
    - HR PWM pins are not remapable: https://www.microchip.com/forums/m1186202.aspx
    - RGB LED, BLUE Channel, pin `RP46/PWM1H/RB14` - PWM usable from Master
    - RGB LED, GREEN Channel, pin `S1RP71/S1PWM8H/S1RD7` - PWM usable from Slave only
    - RGB LED, RED Channel, pin `S1RP69/S1PWM6L/S1RD5` - PWM usable from Slave only, also
      notice that RED Channel is connected to PWM LOW pin, so other PWM registers are needed.
  - how to use: press S1 to increase RED brightness, S2 to increase GREEN brightness
    and S3 to increase BLUE brightness. It will wrap on overflow. Please be aware that LEDs
    are non-linear semiconductors so the brigthness has logarithm like curve (very sensitive
    to low values change and insesitive to high values change).

