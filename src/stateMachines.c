#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

static int count = 0;
static char dim = 0;

void turn_on_red()		/*turn on red, turn off green */
{
  red_on = 1;
  green_on = 0;
  led_update();
}

void turn_on_green()	/* turn on green, turn off red */
{
  green_on = 1;
  red_on = 0;
  led_update();
}

void both_on() /*turn both leds on*/
{
  green_on = 1;
  red_on = 1;
  led_update();
}

void off_state() /*state to turn off the toy*/
{
  buzzer_set_period(0);
  red_on = 0;
  
  led_update();
  clearScreen(COLOR_BLACK);
}

void toggle_leds() /*toggle between red and green*/
{
  buzzer_set_period(1000);
  static char state = 0;
  switch(state){
    case 0:
      red_on = 1;
      green_on = 0;
      led_update();
      state = 1;
      break;
    case 1:
      green_on = 1;
      red_on = 0;
      led_update();
      state = 0;
      break;
  }
}

void siren_on()
{
  clearScreen(COLOR_GREEN);
  if(count == 2500){
    buzzer_set_period(0);
    count = 0;
  }
  if (count < 200) buzzer_set_period(5000);
  else if (count < 400) buzzer_set_period(0);
  else if (count < 600) buzzer_set_period(2000);
  else if (count < 800) buzzer_set_period(0);
  else if (count < 1000) buzzer_set_period(4444);
  else if (count < 1200) buzzer_set_period(0);
  else if (count < 1400) buzzer_set_period(6000);
  else if (count < 1600) buzzer_set_period(0);
  else if (count < 1800) buzzer_set_period(3250);
  else if (count < 2000) buzzer_set_period(0);
  else if (count < 2200) buzzer_set_period(5000);
  else if (count < 2400) buzzer_set_period(0);
  else if (count < 2450) buzzer_set_period(1000);
  count +=2;
}
/*
void dim_red()
{
  switch(dim){
  case 0:
    red_on = 1;
    dim++;
    break;
  case 1:
  case 2:
  case 3:
    red_on = 0;
    dim = 0;
    break;
  }
  //led_changed = 1;
  led_update();
    
}
*/
void shape_sides()
{
  u_char size = 15;
  u_char w = screenWidth/4;
  u_char h = screenHeight/4;
  clearScreen(COLOR_PINK);
  
  for(u_char r = 0; r < size; r++){
    for(u_char c = 0; c < r; c++){
      drawPixel(w-c, h-r-1, COLOR_BLACK);
      drawPixel(w-c, h+r-(2*size), COLOR_BLACK);
      drawPixel(w+c, h-r-1, COLOR_BLACK);
      drawPixel(w+c, h+r-(2*size), COLOR_BLACK);
    }
  }
  drawString5x7(screenWidth/2, screenHeight/2, "4 sides", COLOR_RED, COLOR_BLACK);
}

  /*
void state_advance()		/* alternate between toggling red & green 
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
  
}
*/
