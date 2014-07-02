/*
see README.txt for details.

chris <cliechti@gmx.net>
*/
#include "hardware.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include "lcd.h"
//#include "menu.h"
#if 0

//the font file has no separate header file, it just provides
//the font in this array:
extern const char lcdfont[64];

//redirect stdio to LCD
int putchar(int c) {
    lcdPutc(c);
    return 1;
}

void delay(unsigned int d)
{
  volatile int i;
  for(i = 0; i < d; i++)
    nop();
}


/**
This one is executed once a second. it counts seconds, minutes, hours - hey
it shoule be a clock ;-)
it does not count days, but i think you'll get the idea :-)
*/
wakeup interrupt (TIMERA0_VECTOR) INT_TimerA_CCR0(void) {
    CCR0 += ONESECOND;                  //setup next irq

    pwm_takt++;
    if(RELOUT & REL0)
        kontingent++;

    if (++s > 59) {                     //count seconds, up to one minute
        s = 0;                          //reset seconds and ...
        if (++m > 59) {                 //count miutes, up to one hour
            m = 0;                      //reset minutes and ...
            if (++h > 23) {             //cound hours, up to one day
                h = 0;                  //reset hours and ...
                //++day ...             //don't do anything, could count days here
            }
        }
    }
}

//int keycounter[8];
//Interrupt Routine

int keymap = 0;
wakeup interrupt (PORT2_VECTOR) Port2_Interrupt (void)
{
    delay(1000);
    //int pstate = P2IN;
    /*
    for(i =0;i<8;i++){
        if((P2IFG & (0x01<<i))==(0x01<<i))   //Wenn Flag von P2.0 gesetzt ist
        {
            keycounter[i]++;
        }
    }
    */
    //for(int i = 0;i<10;++i){

    //    delay(2000);
    //}
    //keymap = P2IFG & (TASTE_HOCH|TASTE_RUNTER|TASTE_LINKS|TASTE_RECHTS);
    keymap = (~P1IN) & (TASTE_HOCH|TASTE_RUNTER|TASTE_LINKS|TASTE_RECHTS);
    //P2OUT ^= LED;
    P2IFG =0;   //Inerruptflag zurücksetzen
}

void initPorts(){
    P1OUT  = 0;                //Init output data of port1
    P2OUT  = 0;                //Init output data of port2

    P1SEL  = 0;                //Select port or module -function on port1
    P2SEL  = 0;                //Select port or module -function on port2

    P1DIR  = 0xFF;                //Init port direction register of port1
    P2DIR  = 0xFF;                //Init port direction register of port2

    P1IES  = 0;                //init port interrupts
    P1IE   = 0;
}
void initADC(){
    //ADC12 settings
    //ADC12CTL0 = ADC12ON+SHT0_0+MSC+REFON+REF2_5V;  // ADC12 anschalten, n=1, mehrere konvertierungen, referenz auf 2,5V setzen
    ADC12CTL0 = ADC12ON+SHT0_0+MSC+REFON;  // ADC12 anschalten, n=1, mehrere konvertierungen, referenz auf 2,5V setzen
    ADC12CTL1 = SHP+CONSEQ_1;  // SHP benutzen, sequence of channels genau 1 mal konvertieren (P6.0 und P6.1)
    ADC12MCTL0 = SREF_0+INCH_0;  // Vr+=Vref+
    ADC12MCTL1 = SREF_1+INCH_1;  // Vr+=Vref+
    ADC12MCTL2 = SREF_0+INCH_2;  // Vr+=Vref+
    ADC12MCTL3 = SREF_0+INCH_3+EOS;  // Vr+=Vref+
    ADC12CTL0 |= ENC;       // jetzt anfangen ...
}
void initTimer(){
    BCSCTL1 |= DIVA0 | DIVA1;           //setup divider for RTC
    TACTL  = TACTL_INIT;                //setup timer (still stopped)
    CCR0   = ONESECOND;                 //setup first RTC irq
    CCTL0  = CCIE;                      //enable compare interrupts
    CCTL1  = 0;                         //the other modules are not used
    CCTL2  = 0;                         //...
    TACTL  |= MC1;                      //start timer
}

void initPeriferals(){
    WDTCTL = WDTCTL_INIT;               //Init watchdog timer
    initPorts();
    initADC();
    initTimer();
}

/**
Main function with init an an endless loop that is synced with the
interrupts trough the lowpower mode.
*/
int main(void) {
    //int i = 0;

    initPeriferals();

                                //enable interrupts
    pwm_takt = 0;
    h = m = s = 0;
    kontingent = 0;
    tempZuViel = 0;

    globals.pwm_breite = 5*60;
    globals.pwm_periode = 10*60;
    globals.kontingent_minimum = 60*60;
    globals.kontingent_startstunde = 18;
    globals.sonne_hysterese = 200;
    globals.sonne_schwelle = 2000;
    globals.temp_messpunkt = 2*60;
    globals.temp_schwelle = 1300;

    struct savestruct * flashptr = (struct savestruct *)0x1000;

    if(flashptr->pwm_periode!=0xFFFF){
        globals = *flashptr;
    }

    //P2OUT |= LED;                       //light LED during init
    lcdOn();                            //reset sequence
    lcdInit();                          //setup LCD modes
    //lcdDownloadFont(lcdfont, sizeof(lcdfont));
    //P2OUT &= ~LED;                      //switch off LED
    //puts("Hi, I'm a clock");            //say hello
    initMenu();



    while (1) {                         //main loop, never ends...
        //show the clock
        //as we are synced with the interrupt, its save to read h,m,s
        //otherwise a dint..eint around the following line would be
        //very helpful to prevent bogus values
        //printf("%02d:%02d:%02d", h, m, s);
        //lcdInstr(LCD_LINE1);

        //printf("%04d%04d%04d%04d", keycounter[0],keycounter[1],keycounter[2],keycounter[3]);

        //lcdInstr(LCD_LINE2);
        /*
        int i;
        for(i=0;i<8;i++){
            if((P2IN & 1<<i)){
                putchar(7);
            }else{
                putchar(1);
            }
        }
        */
        //ADC12 ausgabe
        ADC12CTL0 |= ADC12SC; // konvertierung durchfuehren
        while(ADC12BUSY & ADC12CTL1){
            nop();
        }
        if (ADC12MEM0 <= 0x7FF)
            P2OUT &= ~LED;       // rote LED aus
        else
            P2OUT |= LED;   // rote LED an
        //printf("%04d%04d%04d%04d",ADC12MEM0,ADC12MEM1,ADC12MEM2,ADC12MEM3);


        //printf("    %02d:%02d:%02d",h, m, s);

        //now show the bargraph. it hasn't to do much with a clock
        //but we want to show the feature here...
        //lcdInstr(LCD_LINE2+15);
        //putchar(i);

        //if (++i >= 8) i = 0;            //lets show all 8 downloadable chars
        //P3OUT ^= 0x1E;
        checkMitternacht();
        checkkeys(keymap);
        keymap = 0;
        drawmenu();
        eint();
        LPM0;                           //sync, wakeup by irq
        dint();

        int relais = RELOUT;
        //Ausgang 1 testen
        relais &= ~(REL0);
        if(checkKontingent()){
            relais |= REL0;
        }else{
            if((checkFiveMin() && checkSonne())){
                if(checkTemp()){
                    relais |= REL0;
                }
            }
        }

        //Ausgang 2 testen
        if(checkSonne()){
            relais |=  REL1 ;
        }else{
            relais &= ~( REL1 );
        }
        RELOUT = relais;
    }
}


#endif

#include "lcd2.h"
unsigned int currentMinutes, currentSeconds;

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= BIT0;					// Toggle LED
}

int main()
{
    WDTCTL = WDTPW + WDTHOLD;			// Stop WDT

    BCSCTL1 |= DIVA_3;				// ACLK/8
    BCSCTL3 |= XCAP_3;				//12.5pF cap- setting for 32768Hz crystal

    P1DIR |= BIT0;					// set P1.0 (LED1) as output
    P1OUT |= BIT0;					// P1.0 low

    currentMinutes = 0;
    currentSeconds = 0;

    InitializeLcm();
    ClearLcmScreen();

    CCTL0 = CCIE;					// CCR0 interrupt enabled
    CCR0 = 511;					// 512 -> 1 sec, 30720 -> 1 min
    TACTL = TASSEL_1 + ID_3 + MC_1;			// ACLK, /8, upmode


    PrintStr("Hallo Welt!");


    _BIS_SR(LPM3_bits + GIE);			// Enter LPM3 w/ interrupt
    return 0;
}
