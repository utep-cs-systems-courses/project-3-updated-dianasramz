#ifndef switches_included
#define switches_included

#include "msp430.h"
static unsigned char switch_mask;
static unsigned char switches_last_reported;
static unsigned char switches_current;


extern char bState;
unsigned int p2sw_read();
void p2sw_init(unsigned char mask);
void switch_inerrupt_handler();

#endif // included
