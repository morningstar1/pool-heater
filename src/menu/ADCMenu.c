/*
 * ADCMenu.c
 *
 *  Created on: 17.05.2009
 *      Author: Sebastian
 */

#include "../hardware.h"
#include "../menu.h"
#include "ADCMenu.h"


//Stunde
void drawADC(void){
    lcdInstr(LCD_LINE1);
    printf("ch1 %04dch2 %04d",ADC12MEM0,ADC12MEM1);
    lcdInstr(LCD_LINE2);
    printf("ch3 %04dch4 %04d",ADC12MEM2,ADC12MEM3);
}

void ADCKeyUp(void){
}
void ADCKeyDown(void){
}

struct menupunkt menuADC;
struct menupunkt * initADCMenu(){
    menuADC.drawMenu = drawADC;
    menuADC.KeyUp = ADCKeyUp;
    menuADC.KeyDown = ADCKeyDown;
    return &menuADC;
}
