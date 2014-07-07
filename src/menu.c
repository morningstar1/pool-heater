/*
 * menu.c
 *
 *  Created on: 16.05.2009
 *      Author: Sebastian
 */

#include "menu.h"

int menucount = 13;
struct menupunkt* menus[13];

void initMenu(){
    int i = 0;
    menus[i++] = initUhrStunde();
    menus[i++] = initUhrMinute();
    menus[i++] = initADCMenu();
    menus[i++] = initPWMBreite();
    menus[i++] = initPWMPeriode();
    menus[i++] = initSonne();
    menus[i++] = initHysterese();
    menus[i++] = initKontingent();
    menus[i++] = initKontingentStunde();
    menus[i++] = initFlash();
    menus[i++] = initFlashSave();
    menus[i++] = initTemp();
    menus[i++] = initTempMesspunkt();
    menucount = i;
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
        InitializeLcm();
        ClearLcmScreen();
    }
    if(keymap & TASTE_RUNTER){
        (*menus[currentmenu]).KeyDown();
    }
    if(keymap & TASTE_HOCH){
        (*menus[currentmenu]).KeyUp();
    }

    if(currentmenu >= menucount)
        currentmenu = 0;
    if(currentmenu < 0)
        currentmenu = menucount - 1;
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
