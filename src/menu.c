/*
 * menu.c
 *
 *  Created on: 16.05.2009
 *      Author: Sebastian
 */

#include "menu.h"

int menucount = 12;
struct menupunkt* menus[12];

void initMenu(){
    menus[0] = initUhrStunde();
    menus[1] = initUhrMinute();
    menus[2] = initADCMenu();
    menus[3] = initPWMBreite();
    menus[4] = initPWMPeriode();
    menus[5] = initSonne();
    menus[6] = initKontingent();
    menus[7] = initKontingentStunde();
    menus[8] = initFlash();
    menus[9] = initFlashSave();
    menus[10] = initTemp();
    menus[11] = initTempMesspunkt();
}

int currentmenu = 2;
void checkkeys(int keymap){
    if(keymap & TASTE_RECHTS){
        ++currentmenu;
    }
    if(keymap & TASTE_LINKS){
        --currentmenu;
    }
    if(keymap & (TASTE_LINKS | TASTE_RECHTS)){
        lcdOn();                            //reset sequence
        lcdInit();                          //setup LCD modes
    }
    if(keymap & TASTE_RUNTER){
        (*menus[currentmenu]).KeyDown();
    }
    if(keymap & TASTE_HOCH){
        (*menus[currentmenu]).KeyUp();
    }

    if(currentmenu >= menucount)
        currentmenu =0;
    if(currentmenu <0)
        currentmenu = menucount-1;
}
void drawmenu(){
    (*menus[currentmenu]).drawMenu();
}

void checkMitternacht(){
    if(h==0&&m==0&&s==0){
        kontingent = 0;
        tempZuViel = 0;
    }
}
