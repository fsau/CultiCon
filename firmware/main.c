#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/cpufunc.h>
#include <avr/sleep.h>
#include <util/atomic.h>

FUSES =
{
    .low = (LFUSE_DEFAULT),
    .high = (HFUSE_DEFAULT),
};

#define F_CPU 8000000UL
#include <util/delay.h>

// definitions/macros:
#define SET_FLAG(x) (g_flags|=(x))
#define CLEAR_FLAG(x) (g_flags&=~(x))
#define TOGGLE_FLAG(x) (g_flags^=(x))
#define FLAG_IS_SET(x) (g_flags&(x))
#define FLAG_IS_CLEAR(x) (~g_flags&(x))
#define MAXOF(x,y) (((x)>(y))?(x):(y))
#define MINOF(x,y) (((x)<(y))?(x):(y))

// function prototypes:
uint8_t get_i2c_hour(void);

// global variables:

// eeprom variables:

void
main (void)
{
  // uint8_t initial_s = MCUSR;
  // MCUSR = 0;
  wdt_enable(WDTO_250MS);
  wdt_reset();

  while(1) // main loop
  {
    wdt_reset();
  }
}

// interrupts:
ISR(INT0_vect)
{
  
}

// functions:

uint8_t
get_i2c_hour(void)
{

}
