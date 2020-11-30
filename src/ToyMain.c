#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdtypes.h"
#include "p2switches.h"
#include "stateMachines.h"

#define LED_GREEN BIT6
short redrawScreen = 1;

void wdt_c_handler()
{
  static int count = 0;

  count++;
  if( count == 250){
    count = 0;
    redrawScreen = 1;
  }
}

int main(void){
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks(); //setup master oscillator, CPU & peripherial
  p2sw_init();
  buzzer_init();
  led_init();
  enableWDTInterrupts(); //enable periodic interrupts
  lcd_init();

  or_sr(0x8); //CPU off, GIE on

  clearScreen(COLOR_WHITE); 
}
