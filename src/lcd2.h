#ifndef LCD2_H
#define LCD2_H

void InitializeLcm();
void ClearLcmScreen();
//void PrintStr(const char * string);
void lcdInstr( char cmd );

#define LCD_LINE1       0x80                    ///< Address offset for 1st line in 2-line display mode
#define LCD_LINE2       0xc0                    ///< Address offset for 2nd line in 2-line display mode

#endif // LCD2_H
