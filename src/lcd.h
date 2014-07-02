/**
LCD functions, header file.

chris <cliechti@gmx.net>
*/
#ifndef LCD_H
#define LCD_H

//Instructions for LCD chip
/** Switch on display.
<B>IMPORTANT:</B> <code>lcdDelay(LCDDELAY2)</code> must be called after
this instruction because the display contoller needs some additional time.
*/
#define LCD_ON              0x01 //0x00000001 //Switch on  display
#define LCD_OFF             0x08 //0x00001000 //Switch off display

//#define LCDEMODE      0x06 //0x00000110
//#define LCDFONT       0x21 //0x00100001

/** Clear the display. */
#define LCD_CLEAR           0x01 //0x00000001

/** Place cursor on a specific display line. The horizontal offset
can be added: LCDLINEx + xoffset. As the line length is limited,
the horizontal offset must not be greater 64
*/
#ifdef LCD_4LINETYPE
    //~ #message "lcd.h: 4 Line LCD selected"
    // 4 line display
    #define LCD_LINE1       0x80                    ///< Address offset for 1st line in 4-line display mode
    #define LCD_LINE2       0xa0                    ///< Address offset for 2nd line in 4-line display mode
    #define LCD_LINE3       0xc0                    ///< Address offset for 3rd line in 4-line display mode
    #define LCD_LINE4       0xe0                    ///< Address offset for 4th line in 4-line display mode
    #define LCD_LINEWIDTH   0x20                    ///< Specify the line with in 4-line display mode
#else   // LCD_4LINETYPE
    //~ #message "lcd.h: 2 Line LCD selected"
    // 2 line display
    #define LCD_LINE1       0x80                    ///< Address offset for 1st line in 2-line display mode
    #define LCD_LINE2       0xc0                    ///< Address offset for 2nd line in 2-line display mode
    #define LCD_LINEWIDTH   0x40                    ///< Specify the line with in 2-line display mode
#endif  // LCD_4LINETYPE

/** Cursor modes.
*/
#define LCD_CURSORON        0x0f //0x00001111 //turn on cursor blinking
#define LCD_CURSOROFF       0x0c //0x00001100 //Disable cursor blinking. The cursor is hidden.


/** these are used for the LCD init and module internally
*/
//Bitpatters for LCDOUT
#define LCD_8BITS           0x30 //0b00110000 //select 8 Bit interface
#define LCD_4BITS           0x20 //0b00100000 //select 4 Bit interface
#define LCD_DATA_OFF        0x05 //0x00000101 //mask used to clear the data lines

//some instructions
#define LCD_FUNCTIONSET     0x20                    ///< LCD function set instruction
#define LCD_2LINES          0x08                    ///< Bitmask for the \c LCD_FUNCTIONSET to set the 2-line display mode
#define LCD_RE_BIT          0x04                    ///< Bitmask for the \c LCD_FUNCTIONSET to select the extension register (set RE bit)

#define LCD_EXT_FUNCTIONSET 0x08                    ///< LCD extended function set instruction
#define LCD_4LINES          0x01                    ///< Bitmask for the \c LCD_EXT_FUNCTIONSET to set the 4-line display mode

#define LCD_DISP_CTRL       0x08                    ///< LCD ON/OFF control instruction
#define LCD_DISP_ON         0x04                    ///< Bitmask for the \c LCD_DISP_CTRL to turn on the display (visible).

#define LCD_ENTRYMODE       0x04                    ///< LCD entry mode set
#define LCD_INC             0x02                    ///< Bitmask for the #LCD_ENTRYMODE to set the cursor moving direction

#define LCD_CLEAR           0x01                    /**< Instruction to clear the display.
                                                    @note This instructions use much more execution time then an other instruction.
                                                    @warning The data book says not more then 1.53ms but in fact its 2ms.
                                                    Call <code>lcdDelay(LCD_DELAY_2MS)</code> after using this instruction! */

#define LCD_HOME            0x02                    /**< Instruction to set the cursor to the home position.
                                                    @note This instructions use much more execution time then an other instruction.
                                                    @warning The data book says not more then 1.53ms but in fact its 2ms.
                                                    Call <code>lcdDelay(LCD_DELAY_2M)</code> after using this instruction! */

#define LCD_CGRAM           0x40                    /**< Set the address pointer in CGRAM. An additionally offset can be added.
                                                    @note The CGRAM is limited to 64 bytes. The offset can not exeed 64. */

#define LCD_DDRAM           0x80                    /**< Set the address pointer in DDRAM. An additionally offset can be added.
                                                    For direct access to the individual lines use the definitions like #LCD_LINE1.
                                                    @note The DDRAM is limited to 128 bytes. The offset can not exeed 128. */

//forward declarations
void lcdOn( void );
void lcdInstr( char cmd );
void lcdPutc( char c );
void lcdInit( void );
void lcdDelay(unsigned int d);
#ifdef LCD_EXTRA
void lcdPuts( char * str );
void lcdDownloadFont( const void * fontdata, int size);
#endif //LCD_EXTRA

#endif /*LCD_H*/

