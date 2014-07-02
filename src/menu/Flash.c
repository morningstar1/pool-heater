/*
 * Flash.c
 *
 *  Created on: 22.05.2009
 *      Author: Sebastian
 */

#include "../menu.h"
#include "flash.h"


unsigned char* flash_current_adress = (unsigned char*)0x1000;

void drawFlash(void){
    lcdInstr(LCD_LINE1);
    printf("Adresse: <%04X> ",(unsigned int)flash_current_adress);
    lcdInstr(LCD_LINE2);
    int i;
    for(i=0;i<8;i++){
        printf("%02X",flash_current_adress[i]);
    }
}
void drawFlashSave(void){
    lcdInstr(LCD_LINE1);
    printf("Speichern?     !");
    lcdInstr(LCD_LINE2);
    printf("TASTE HOCH      ");
}

void FlashKeyUp(void){
    flash_current_adress+=8;
}


void saveToFlash(struct savestruct *quelle){
    struct savestruct *ptrFlash = (struct savestruct *)0x1000;

    unsigned int *ptrlf = (unsigned int*)ptrFlash;
    FCTL1 = 0x0A502;
    FCTL3 = 0x0A500;
    *ptrlf=0xFF;
    int i;
    for(i=0; i<1000; i++)
        nop();

    while(BUSY & FCTL3);
    FCTL3 = FWKEY;
    FCTL1 = FWKEY + WRT;
    *ptrFlash = *quelle;
    FCTL1 = FWKEY;
    FCTL3 ^= (FXKEY + LOCK);

}
void FlashSaveKeyUp(void){
    saveToFlash(&globals);
}
void FlashKeyDown(void){
    flash_current_adress-=8;
}
void FlashSaveKeyDown(void){
}
struct menupunkt menuFlash;
struct menupunkt * initFlash(){
    menuFlash.drawMenu = drawFlash;
    menuFlash.KeyUp = FlashKeyUp;
    menuFlash.KeyDown = FlashKeyDown;
    return &menuFlash;
}
struct menupunkt menuFlashSave;
struct menupunkt * initFlashSave(){
    menuFlashSave.drawMenu = drawFlashSave;
    menuFlashSave.KeyUp = FlashSaveKeyUp;
    menuFlashSave.KeyDown = FlashSaveKeyDown;
    return &menuFlashSave;
}
