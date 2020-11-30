#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char bState;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec 
  static char blink_count = 0;
  if (++blink_count == 125) {
    state_advance();
    blink_count = 0;
  }
					*/
  switch(bState){
    case 1:
      toggle_leds();
      break;
    case 2:
      turn_on_red();
      siren_on();
      break;
    case 3:
      dim_green();
      break;
    case 4:
      off_state();
      break;
    default:
      break;
  }
    
}
