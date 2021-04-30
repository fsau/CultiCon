/*
Copyright (C) 2021 Franco Sauvisky
This file is part of CultiCon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
