#ifndef HARDWARE_H
#define HARDWARE_H

#include <msp430.h>
//#include <signal.h>
#include <iomacros.h>
#include  <msp430g2553.h>

//PINS
//PORT1
#define LCD_RS          BIT0
#define LCD_RW          BIT1
//#define LCD_E           BIT3
#define LCD_D4          BIT2
#define LCD_D5          BIT3
#define LCD_D6          BIT4
#define LCD_D7          BIT5

//PORT2
#define LED             BIT2

//for the lcd.c module
#define LCDOUT          P2OUT
#define LCDDIR          P2DIR
//#define LCDIN           P2IN
//customize this if your MSP runs at different speed.
#define LCDDELAY1MS     750                     // ~1ms @750kHz

//Ausgänge
#define RELOUT            P1OUT
#define REL0            BIT2
#define REL1            BIT3

#define TASTE_IN        P1IN
#define TASTE_HOCH        BIT4
#define TASTE_RUNTER    BIT5
#define TASTE_RECHTS    BIT6
#define TASTE_LINKS        BIT7

#define SONNENSENSOR    ADC12MEM0
#define TEMPERATURSENSOR    ADC12MEM1
//Port Output Register 'P1OUT, P2OUT':
#define P1OUT_INIT      0                       // Init Output data of port1
#define P2OUT_INIT      0                       // Init Output data of port2

//Port Direction Register 'P1DIR, P2DIR':
#define P1DIR_INIT      0xff                    // Init of Port1 Data-Direction Reg (Out=1 / Inp=0)
#define P2DIR_INIT      0x20                    // Init of Port2 Data-Direction Reg (Out=1 / Inp=0)

//Selection of Port or Module -Function on the Pins 'P1SEL, P2SEL'
#define P1SEL_INIT      0                       // P1-Modules:
#define P2SEL_INIT      0                       // P2-Modules:

//Interrupt capabilities of P1 and P2
#define P1IE_INIT       0                       // Interrupt Enable (0=dis 1=enabled)
#define P2IE_INIT       0xdf //df                    // Interrupt Enable (0=dis 1=enabled)
#define P1IES_INIT      0                       // Interrupt Edge Select (0=pos 1=neg)
#define P2IES_INIT      0xdf                       // Interrupt Edge Select (0=pos 1=neg)

#define IE_INIT         0
#define WDTCTL_INIT     WDTPW|WDTHOLD

#define TACTL_INIT      TASSEL0|TACLR|ID_3      //ACLK, /8
#define ONESECOND       512                     //32768/8/16

// LCD options
#define LCD_EXTRA

#endif //HARDWARE_H
