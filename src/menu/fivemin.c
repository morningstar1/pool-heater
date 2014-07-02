/*
 * fivemin.c
 *
 *  Created on: 21.05.2009
 *      Author: Sebastian
 */
#include "fivemin.h"
#include "../menu.h"

int checkFiveMin(){
    int ret =0;
    if(pwm_takt >= globals.pwm_periode)
        pwm_takt = 0;
    if(pwm_takt < globals.pwm_breite)
        ret = 1;
    return ret;
}

void drawPWMBreite(void){
    lcdInstr(LCD_LINE1);
    printf("5 min (in s) t1 ");
    lcdInstr(LCD_LINE2);
    printf("<%03d> %03d  - %03d",globals.pwm_breite,globals.pwm_periode,pwm_takt);
}
void drawPWMPeriode(void){
    lcdInstr(LCD_LINE1);
    printf("5 min (in s) T  ");
    lcdInstr(LCD_LINE2);
    printf(" %03d <%03d> - %03d",globals.pwm_breite,globals.pwm_periode,pwm_takt);
}
void PWMBreiteKeyUp(void){
    globals.pwm_breite++;
}

void PWMBreiteKeyDown(void){
    globals.pwm_breite--;
}
void PWMPeriodeKeyUp(void){
    globals.pwm_periode++;
}

void PWMPeriodeKeyDown(void){
    globals.pwm_periode--;
}
struct menupunkt menuPWMBreite;
struct menupunkt * initPWMBreite(){
    menuPWMBreite.drawMenu = drawPWMBreite;
    menuPWMBreite.KeyUp = PWMBreiteKeyUp;
    menuPWMBreite.KeyDown = PWMBreiteKeyDown;
    return &menuPWMBreite;
}
struct menupunkt menuPWMPeriode;
struct menupunkt * initPWMPeriode(){
    menuPWMPeriode.drawMenu = drawPWMPeriode;
    menuPWMPeriode.KeyUp = PWMPeriodeKeyUp;
    menuPWMPeriode.KeyDown = PWMPeriodeKeyDown;
    return &menuPWMPeriode;
}
