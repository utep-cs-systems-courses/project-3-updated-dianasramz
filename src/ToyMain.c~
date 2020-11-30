#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

int main(void){
  configureClocks(); //setup master oscillator, CPU & peripherial
  switch_init();
  buzzer_init();
  led_init();
  enableWDTInterrupts(); //enable periodic interrupts

  or_sr(0x18); //CPU off, GIE on
}
