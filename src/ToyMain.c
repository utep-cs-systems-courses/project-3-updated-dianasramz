
#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdtypes.h"
#include "p2switches.h"
#include "stateMachines.h"


#define LED_GREEN BIT6
short redrawScreen = 1;
extern char bState;
static char button = 0;

void wdt_c_handler()
{
  static int count = 0;
  u_int state = p2sw_read();
  
  count++;
  //checking what button is pressed, button is set
  if((state & 1) ==0){
    button = 1;
  }
  if((state & 2) ==0){
    button = 2;
  }
  if((state & 4) ==0){
    button = 3;
  }
  if((state & 8) ==0){
    button = 4;
  }

  switch (button){
  case 1:
    redrawScreen = 1;
    break;
  case 2:
    if(count == 250){
      redrawScreen = 1;
    }
    break;
  case 3:
    if(count == 250){
      redrawScreen = 1;
      count = 0;
    }
    break;
  case 4:
    if(count == 250){
      redrawScreen = 1;
      count = 0;
    }
    break;
  }

  if(count == 250){
    count = 0;
  }
  
}

void main(){
  led_init();
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  
  configureClocks(); //setup master oscillator, CPU & peripherial
  p2sw_init(15);

  buzzer_init();
  lcd_init();
  
  enableWDTInterrupts(); //enable periodic interrupts

  or_sr(0x8); //CPU off, GIE on

  clearScreen(COLOR_WHITE);
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      switch(bState){
      case 1:
       	led_advance();
	//	dim_red_state();
	//dim_red25();
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
