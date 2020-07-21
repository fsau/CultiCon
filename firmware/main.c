#define F_CPU 8000000UL
#define BAUD 9600
#include "pinout_def.h"

// global variables:
clock_time g_ctime;

// eeprom variables:
clock_time EEMEM turn_on, turn_off;
uint8_t EEMEM tpow_on, tpow_off;

// functions:
#include "gfunctions.c"

// interrupts:
#include "interrupts.c"

// main:
void
main (void)
{
  uint8_t initial_s = MCUSR;
  MCUSR = 0;
  wdt_enable(WDTO_250MS);
  wdt_reset();

  while(1) // main loop
  {


    wdt_reset();
  }
}
