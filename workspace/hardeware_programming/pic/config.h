#ifndef CONFIG_H
#define CONFIG_H

// CONFIG1H
#pragma config OSC = INTIO67      // Internal oscillator, port function on RA6/RA7
#pragma config FCMEN = OFF        // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF         // Internal/External Oscillator Switchover disabled

// CONFIG2L
#pragma config PWRT = OFF         // Power-up Timer disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset disabled
#pragma config BORV = 3           // Brown-out Voltage = 2.1V

// CONFIG2H
#pragma config WDT = OFF          // Watchdog Timer disabled
#pragma config WDTPS = 32768      // Watchdog Timer Postscale 1:32768

// CONFIG3H
#pragma config CCP2MX = PORTC     // CCP2 input/output is multiplexed with RC1
#pragma config PBADEN = OFF       // PORTB<4:0> pins configured as digital I/O on Reset
#pragma config LPT1OSC = OFF      // Timer1 configured for higher power operation
#pragma config MCLRE = ON         // MCLR pin enabled; RE3 input pin disabled

// CONFIG4L
#pragma config STVREN = ON        // Stack full/underflow will cause Reset
#pragma config LVP = OFF          // Single-Supply ICSP disabled
#pragma config XINST = OFF        // Extended Instruction Set disabled
#pragma config DEBUG = OFF        // Background debugger disabled

// CONFIG5L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
#pragma config CPB = OFF, CPD = OFF

// CONFIG5H
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
#pragma config CPB = OFF, CPD = OFF

// CONFIG6L
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF

// CONFIG6H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF

// CONFIG7L
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
#pragma config EBTRB = OFF

// CONFIG7H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
#pragma config EBTRB = OFF

#endif


