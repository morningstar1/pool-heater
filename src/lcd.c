/**
Functions for simplified LCD usage. This module is for HD44780 and compatible
display controllers. Note that this controller has a display
memory for two lines with 64 characters on each, but most displays
only show a part of them. The displayed are can be scrolled in such a
case.

Usual way to start-up the display:
    lcdOn();
    lcdInit();
 optional: lcdDownloadFont(font, size);
 optional: configure cursor, set cursor position:<UL>
        lcdInstr(LCDLINE1 + x)
        lcdInstr(LCDLINE2 + x)

very useful ;-) write some text using:
    lcdPuts("text");
    lcdPutc('c');

Some instruction need special care, see lcdInstr() for details.

chris <cliechti@gmx.net>
*/

#include "hardware.h"
#include "lcd.h"

/**
Wait until LCD signals that it is ready
*/
void lcdBusy(void) {
    char busy;

    LCDDIR = (char)~(LCD_D4|LCD_D5|LCD_D6|LCD_D7); //
    LCDOUT = LCD_RW;            //read out satus
    do {
        //read out the high nibble with the BF flag
        LCDOUT |= LCD_E;        //toggle LCD_E, the enable pin
        nop();
        busy = LCDIN & LCD_D7;  //poll buy flag
        LCDOUT &= ~LCD_E;       //back to inactive position
        //read out the low nibble, ignore it
        LCDOUT |= LCD_E;        //toggle LCD_E, the enable pin
        LCDOUT &= ~LCD_E;       //back to inactive position
    } while (busy);
    LCDDIR = LCD_D4|LCD_D5|LCD_D6|LCD_D7|LCD_E|LCD_RW|LCD_RS;
}

/**
Turn on the LCD and initialize it to 4 bit interface.
*/
void lcdOn( void ) {
    LCDOUT  = 0;                //reset pins
    lcdDelay(LCDDELAY1MS*30);   //wait more than 30ms
    //send the reset sequece (3 times the same pattern)
    LCDOUT  = LCD_8BITS;        //set 8 bit interface
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position
    lcdDelay(LCDDELAY1MS*5);    //wait a bit
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position
    lcdDelay(LCDDELAY1MS*5);    //wait a bit
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position
    lcdDelay(LCDDELAY1MS*5);    //wait until instr is finished

    LCDOUT  = LCD_4BITS;        //now set up the 4 bit interface
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position
    lcdBusy();                  //wait until instr is finished
    LCDOUT &= LCD_DATA_OFF;     //reset data lines
}

/**
Write an instruction to the LCD.

There is a short delay after the instruction. This is because the display
controller needs some time execute it. The databook says that 40us are needed
(exceptions, see below). This function makes a delay of approx. 70us @ MCLK=1.5MHz.

Some instructions are defined in the header file. See there for details.

IMPORTANT:
Some instructions use much more time execution time on the display controller.
If such an instruction is used, the user of this function MUST call
lcdDelay(LCDDELAY2) after calling this function!

The instructions where this is needed are:
    LCDON
    LCDCLEAR
*/
void lcdInstr( char cmd ) {
    LCDOUT  = cmd & 0xF0;       //output upper nibble
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position

    LCDOUT  = (cmd << 4) & 0xF0;//and then the lower nibble
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position

    lcdBusy();                  //wait until instr is finished
}

/**
Write a single character in CGRAM or DDRAM of display controller.

When the memory pointer is set to DDRAM (which is the same as the
cursor position), the character is written to the display. The lower 127
charcters are the well-known ASCII symbols. The charachters 0 to 7 are
the user defined characters. The upper 127 characters contain some symbols
and mostly japanese characters. Look at a display manual for a complete
table of usable characters.

See lcdInstr() on how to set the cursor position.

If the memory pointer is set to CGRAM, user defined bitmaps can
be downloaded. Please note that this is better done by
lcdDownloadFont().
*/
void lcdPutc( char c ) {
    LCDOUT  = (c & 0xF0) | LCD_RS;//output upper nibble
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position

    LCDOUT  = ((c << 4) & 0xF0) | LCD_RS; //and then the lower nibble
    LCDOUT |= LCD_E;            //toggle LCD_E, the enable pin
    LCDOUT &= ~LCD_E;           //back to inactive position

    lcdBusy();                  //wait until instr is finished
}

/**
Read one character from the LCD
*/
unsigned char lcdGetchar(void)
{
    unsigned char c ;
    LCDDIR = (char)~(LCD_D4|LCD_D5|LCD_D6|LCD_D7); //
    LCDOUT = LCD_RW|LCD_RS;      //read out data
    //read out the high nibble with the BF flag
    LCDOUT |= LCD_E;        //toggle LCD_E, the enable pin
    nop();
    c = (LCDIN & 0xf0);
    LCDOUT &= ~LCD_E;       //back to inactive position
    //read out the low nibble, ignore it
    LCDOUT |= LCD_E;        //toggle LCD_E, the enable pin
    c |= (LCDIN & 0xf0) >> 4;
    LCDOUT &= ~LCD_E;       //back to inactive position
    LCDDIR = LCD_D4|LCD_D5|LCD_D6|LCD_D7|LCD_E|LCD_RW|LCD_RS;
    return c;
}

/**
Initialize the display with two lines, cursor hidden and clear
display.

The user might want to call lcdDownloadFont() after
this function to complete the display setup.
*/
void lcdInit( void ) {
    #ifdef LCD_4LINETYPE
        // select the extension register (set RE bit)
        lcdInstr(LCD_FUNCTIONSET | LCD_RE_BIT);
        // set the 4-line display mode
        lcdInstr(LCD_EXT_FUNCTIONSET | LCD_4LINES);
        // clear RE bit
        lcdInstr(LCD_FUNCTIONSET);
    #else
        // set the 2-line display mode
        lcdInstr(LCD_FUNCTIONSET | LCD_2LINES);
    #endif
    lcdInstr(LCD_CURSOROFF);     //hide cursor
    lcdInstr(LCD_CLEAR);         //clear display
}

/**
Unspecific delay function (busy wait type).
this small assembler bit does not need any C init etc. so
we can use the attribute "naked"
*/
__attribute__ ((naked)) void lcdDelay(unsigned int n) {
    //first arg comes in register R15
    //the loop uses 3 cycles per round
    //the eight cycles come from the call overhead and ret
    //
    //delay_time = (1/MCLK)*(8+(3*n))
    asm("lcdloop: dec %0\n  jnz lcdloop\n ret" :: "r" (n));
}

#ifdef LCD_EXTRA
/**
Write a string in CGRAM or DDRAM of display controller. It uses
NULL terminated strings, whitch is usual in C code.

As this function is based on <code>lcdPutchar()</code>, you may
want to have a look at its documentation about the details.

Writing a character to the display needs ~60us. Including setting
the cursor on a specific position (lcdInstr(LCDLINEy + x))
*/
void lcdPuts( char * str ) {
    while (*str != 0) {
        lcdPutc(*str++);        //write char and increment pointer
    }
}

/**
Write font data in CGRAM. This function is intended to download the
user definable characters to the display. These are 8 bytes per
characte and our display has eight free programmable characters. This
makes a maximum of 64 bytes (the function has a limit of ~32000 bytes,
but the display controller is limited).

This function always starts with downloading the user charcter 0. If you
want to replace some characters during program the following procedure
is recomended:
    - Download all eight characters. The ones that never change
      are located at the end of this font definition.
    - To replace some charactters, e.g. two. you use this
      function to download 16 bytes from an other font,
      which overwrite the first two character bitmaps.
    - Switching back to the original charachters is done
      by downloading 16 bytes (or all 64 bytes) from the
      same pointer as in point 1.

Charcter data is specified in the following way:
//Font
const unsigned char lcdfont[] = {
    //Charchter 0
  0x0a,   //00001010
  0x15,   //00010101
  0x0a,   //00001010
  0x15,   //00010101
  0x0a,   //00001010
  0x15,   //00010101
  0x0a,   //00001010
  0x15,   //00010101
    //Charchter 1
  0x00,   //00000000
        . . .
        . . .
    //Charchter 7
  0x00,   //00000000
  0x1f,   //00011111
  0x1f,   //00011111
  0x1f,   //00011111
  0x1f,   //00011111
  0x1f,   //00011111
  0x1f,   //00011111
  0x1f,   //00011111
};

As you see only 5x8 pixels are used by the display controller. The
5 pixels in the with are located toward the LSB.
*/
void lcdDownloadFont(const void * fontdata, int size) {
    int i;
    lcdInstr(LCD_CGRAM);
    for (i = 0; i<size; i++) {
        lcdPutc(((unsigned char *)fontdata)[i]);
    }
    lcdInstr(LCD_DDRAM);         //just in case, set cursor to a visible pos
}

#endif //LCD_EXTRA
