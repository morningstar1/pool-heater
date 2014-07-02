/*
 * SonnenSensor.c
 *
 *  Created on: 21.05.2009
 *      Author: Sebastian
 */

/*
 * fivemin.c
 *
 *  Created on: 21.05.2009
 *      Author: Sebastian
 */

#include "../menu.h"
#include "../hardware.h"

int sonne_lastset = 0;
int checkSonne(){

    if(SONNENSENSOR > globals.sonne_schwelle+ (sonne_lastset ? 0 : globals.sonne_hysterese))
        sonne_lastset = 1;
    else
        sonne_lastset = 0;

    return sonne_lastset;
}

void drawSonne(void){
    lcdInstr(LCD_LINE1);
    printf("Sonnenschwelle  ");
    lcdInstr(LCD_LINE2);
    printf("<%06d>        ",globals.sonne_schwelle);
}

void SonneKeyUp(void){
    globals.sonne_schwelle+=10;
}

void SonneKeyDown(void){
    globals.sonne_schwelle-=10;
}

struct menupunkt menuSonne;
struct menupunkt * initSonne(){
    menuSonne.drawMenu = drawSonne;
    menuSonne.KeyUp = SonneKeyUp;
    menuSonne.KeyDown = SonneKeyDown;
    return &menuSonne;
}

