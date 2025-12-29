/*
    PIC18F4580 pins
        1- MCLR/Vpp
        RA0/AN0/Cvref
        RA1/AN1
        RA2/AN2/Vref-
        RA3/AN3/Vref+
        RA4/TOCKI
        RA5/AN4/SS/LVDIN
        RE0/AN5/RD
        RE1/AN6/WR/C1OUT
        RE2/AN7/CS/C2OUT
        Vdd
        Vss
        OSC1/CLKI
        OSC2/CLKO/RA6
        RC0/T1oso/T1CKI
        RC1/T1CKI
        RC2/CCP1
        RC3/SCK/SCL
        RD0/PSP0/C1IN+
        20- RD1/PSP1/C1IN-

        21 - RD2/PSP2/C2IN+
        RD3/PSP3/C2IN-
        RC4/SDI/SDA
        RC5/SDO
        RC6/TX/CK
        RC7/RX/DT
        RD4/PSP4/ECCP1/P1A
        RD5/PSP5/P1B
        RD6/PSP6/P1C
        RD7/PSP7/P1D
        Vss
        Vdd
        RB0/INT0
        RB1/INT1
        RB2/CAN TX/INT2
        RB3/CAN RX
        RB4
        RB5/PGM
        RB6/PGC
        RB7/PDG

    PIC18F4580 with Pickit 3.5
        | PICkit pin | Signal         | PIC18F4580 pin             |
        | ---------- | -------------- | -------------------------- |
        | 1          | **VPP / MCLR** | MCLR / VPP                 |
        | 2          | **VDD**        | VDD                        |
        | 3          | **GND**        | VSS                        |
        | 4          | **PGD**        | RB7 (PGD)                  |
        | 5          | **PGC**        | RB6 (PGC)                  |
        | 6          | PGM            | **NC** (leave unconnected) |


*/

#include <xc.h>

// Simple config - let defaults handle most settings
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 8000000UL

void main(void)
{
    TRISD0 = 0;     // RD0 as output
    LATD0 = 0;      // LED off initially

    while(1)
    {
        LATD0 = 1;       // LED ON
        __delay_ms(500);
        LATD0 = 0;       // LED OFF
        __delay_ms(500);
    }
}




/*
#include <xc.h>
#include "config.h"

#define _XTAL_FREQ 8000000UL   // 8 MHz for delay functions

void main(void)
{
    TRISD0 = 0;     // RD0 as output
    LATD0 = 0;      // LED off initially

    while(1)
    {
        LATD0 = 1;       // LED ON
        __delay_ms(500);

        LATD0 = 0;       // LED OFF
        __delay_ms(500);
    }
}
*/





