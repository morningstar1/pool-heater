/*
 * menuUhr.c
 *
 *  Created on: 17.05.2009
 *      Author: Sebastian
 */

#include "menuUhr.h"

#include "../menu.h"


//Stunde
void drawUhrStunde(void){
    lcdInstr(LCD_LINE1);
    printf("Uhr Stunde      ");
    lcdInstr(LCD_LINE2);
    printf("<%02d>: %02d : %02d   ",h,m,s);
}

void StundeKeyUp(void){
    h++;
    if(h>23){
        h=0;
    }
}
void StundeKeyDown(void){
    h--;
    if(h<0){
        h=23;
    }
}

struct menupunkt menuStunde;
struct menupunkt * initUhrStunde(){
    menuStunde.drawMenu = drawUhrStunde;
    menuStunde.KeyUp = StundeKeyUp;
    menuStunde.KeyDown = StundeKeyDown;
    return &menuStunde;
}

//Minute
void drawUhrMinute(void){
    lcdInstr(LCD_LINE1);
    printf("Uhr Minute      ");
    lcdInstr(LCD_LINE2);
    printf(" %02d :<%02d>: %02d   ",h,m,s);
}

void MinuteKeyUp(void){
    m++;
    if(m>59){
        m=0;StundeKeyUp();
    }
}

void MinuteKeyDown(void){
    m--;
    if(m<0){
        m=59; StundeKeyDown();
    }
}

struct menupunkt menuMinute;
struct menupunkt * initUhrMinute(){
    menuMinute.drawMenu = drawUhrMinute;
    menuMinute.KeyUp = MinuteKeyUp;
    menuMinute.KeyDown = MinuteKeyDown;
    return &menuMinute;
}
