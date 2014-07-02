/*
 * kontingent.c
 *
 *  Created on: 21.05.2009
 *      Author: Sebastian
 */
#include "../menu.h"


int checkKontingent(){
    int ret = 0;

    if(h>= globals.kontingent_startstunde && kontingent <= globals.kontingent_minimum)
        ret = 1;

    return ret;
}

void drawKontingent(void){
    lcdInstr(LCD_LINE1);
    printf("Kontingent in m ");
    lcdInstr(LCD_LINE2);
    printf("%06d - <%05d>",kontingent/60 , globals.kontingent_minimum/60);
}
void drawKontingentStunde(void){
    lcdInstr(LCD_LINE1);
    printf("Kontingentstart ");
    lcdInstr(LCD_LINE2);
    printf("<%02d>:00:00 Uhr  ",globals.kontingent_startstunde);
}
void KontingentKeyUp(void){
    globals.kontingent_minimum+=60;
}

void KontingentKeyDown(void){
    globals.kontingent_minimum-=60;
}
void KontingentStundeKeyUp(void){
    globals.kontingent_startstunde++;
    if(globals.kontingent_startstunde >23)
        globals.kontingent_startstunde = 0;
}

void KontingentStundeKeyDown(void){
    globals.kontingent_startstunde--;
    if(globals.kontingent_startstunde <0)
        globals.kontingent_startstunde = 23;
}

struct menupunkt menuKontingent;
struct menupunkt * initKontingent(){
    menuKontingent.drawMenu = drawKontingent;
    menuKontingent.KeyUp = KontingentKeyUp;
    menuKontingent.KeyDown = KontingentKeyDown;
    return &menuKontingent;
}
struct menupunkt menuKontingentStart;
struct menupunkt * initKontingentStunde(){
    menuKontingentStart.drawMenu = drawKontingentStunde;
    menuKontingentStart.KeyUp = KontingentStundeKeyUp;
    menuKontingentStart.KeyDown = KontingentStundeKeyDown;
    return &menuKontingentStart;
}
