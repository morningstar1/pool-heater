/*
 * menu.h
 *
 *  Created on: 16.05.2009
 *      Author: Sebastian
 */
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "hardware.h"

#include "menu/menuUhr.h"
#include "menu/ADCMenu.h"
#include "menu/fivemin.h"
#include "menu/SonnenSensor.h"
#include "menu/kontingent.h"
#include "menu/Flash.h"
#include "menu/TemperaturSensor.h"

void initMenu();
void drawmenu();
void checkkeys(int keymap);

void checkMitternacht();

struct menupunkt{
    void (*drawMenu)();
    void (*KeyUp)();
    void (*KeyDown)();
};

struct savestruct{
    int pwm_periode;
    int pwm_breite;
    int kontingent_minimum;
    int kontingent_startstunde;
    int sonne_schwelle;
    int sonne_hysterese;
    int temp_schwelle;
    int temp_messpunkt;
};

struct savestruct globals;


//global vars to store the time
int h, m, s;

//zeitmessung für 5 min schaltung
int pwm_takt;

//kontingentmessung
int kontingent;

//temp
int tempZuViel;
