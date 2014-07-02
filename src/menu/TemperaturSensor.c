/*
 * TemperaturSensor.c
 *
 *  Created on: 23.05.2009
 *      Author: Sebastian
 */
#include "../menu.h"
#include "../hardware.h"
int checkTemp(){
    if(tempZuViel){
        return 0;
    }
    if(pwm_takt > globals.temp_messpunkt){
        if(TEMPERATURSENSOR > globals.temp_schwelle){
                return 1;
        }else{
            tempZuViel = 1;
            return 0;
        }
    }else{
        return 1;
    }
}

void drawTemp(void){
    lcdInstr(LCD_LINE1);
    printf("Temp. schwelle  ");
    lcdInstr(LCD_LINE2);
    printf("<%06d> %05d s",globals.temp_schwelle,globals.temp_messpunkt);
}

void drawTempMesspunkt(void){
    lcdInstr(LCD_LINE1);
    printf("Temp. Messpunkt ");
    lcdInstr(LCD_LINE2);
    printf(" %06d <%05d>s",globals.temp_schwelle,globals.temp_messpunkt);
}

void TempKeyUp(void){
    globals.temp_schwelle+=10;
}

void TempKeyDown(void){
    globals.temp_schwelle-=10;
}
void TempMesspunktKeyUp(void){
    globals.temp_messpunkt++;
}

void TempMesspunktKeyDown(void){
    globals.temp_messpunkt--;
}

struct menupunkt menuTemp;
struct menupunkt * initTemp(){
    menuTemp.drawMenu = drawTemp;
    menuTemp.KeyUp = TempKeyUp;
    menuTemp.KeyDown = TempKeyDown;
    return &menuTemp;
}
struct menupunkt menuTempMesspunkt;
struct menupunkt * initTempMesspunkt(){
    menuTempMesspunkt.drawMenu = drawTempMesspunkt;
    menuTempMesspunkt.KeyUp = TempMesspunktKeyUp;
    menuTempMesspunkt.KeyDown = TempMesspunktKeyDown;
    return &menuTempMesspunkt;
}

