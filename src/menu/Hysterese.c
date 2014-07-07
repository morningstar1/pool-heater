/*
 * SonnenSensor.c
 *
 *  Created on: 21.05.2009
 *      Author: Sebastian
 */

/*
 * Hysterese.c
 *
 *  Created on: 07.07.2014
 *      Author: Sebastian
 */

#include "../menu.h"
#include "../hardware.h"

void drawHysterese(void){
    lcdInstr(LCD_LINE1);
    print_lcd("Sonnenhysterese ");
    lcdInstr(LCD_LINE2);
    print_lcd("<%06d>        ", globals.sonne_hysterese);
}

void HystereseKeyUp(void){
    globals.sonne_hysterese+=10;
}

void HystereseKeyDown(void){
    globals.sonne_hysterese-=10;
}

struct menupunkt menuHysterese;
struct menupunkt * initHysterese(){
    menuHysterese.drawMenu = drawHysterese;
    menuHysterese.KeyUp = HystereseKeyUp;
    menuHysterese.KeyDown = HystereseKeyDown;
    return &menuHysterese;
}

