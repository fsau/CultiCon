#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/cpufunc.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

#include "pins-defs.h"
#include "dimmer.h"

// fuses:
FUSES =
{
    .low = (LFUSE_DEFAULT),
    .high = (HFUSE_DEFAULT),
};

#include "dimmer-glue.c"
// #include "adc-helper.c"
// #include "interrupts.c"

void
main (void)
{
  uint8_t initial_s = MCUSR;
  MCUSR = 0;

  wdt_enable(WDTO_250MS);
  wdt_reset();

  // ### main loop ###
  while(1)
  {

  }
}
