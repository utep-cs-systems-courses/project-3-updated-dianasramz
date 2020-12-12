#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdtypes.h"
#include "p2switches.h"
#include "stateMachines.h"
#include "dim_red_state.h"

#define LED_GREEN BIT6
short redrawScreen = 1;
char bState;

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
  led_init();
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  
  configureClocks(); //setup master oscillator, CPU & peripherial
  p2sw_init(15);
  buzzer_init();

  enableWDTInterrupts(); //enable periodic interrupts
  lcd_init();

  or_sr(0x8); //CPU off, GIE on

  clearScreen(COLOR_WHITE);
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      switch(bState){
      case 1:
	dim_red_state();
	break;
      case 2:
	shape_sides();
	break;
      case 3:
	siren_on();
	break;
      case 4:
	off_state();
	break;
      }
    }
  

    P1OUT &= ~LED_GREEN;   /*green off*/
    or_sr(0x10);           /*CPU off*/
    P1OUT |= LED_GREEN;    /*green on*/
  }
}
