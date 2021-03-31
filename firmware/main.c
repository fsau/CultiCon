#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/cpufunc.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "dimmer.h"

// fuses:
FUSES =
{
    .low = ((LFUSE_DEFAULT & FUSE_CKSEL1) | ~(FUSE_CKDIV8&FUSE_CKSEL0)),
    .high = (HFUSE_DEFAULT),
    .extended = (EFUSE_DEFAULT),
};

#include "dimmer-glue.c"
#include "adc-helper.c"
#include "interrupts.c"

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
