#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/cpufunc.h>
#include <avr/sleep.h>
#include <util/atomic.h>

#define F_CPU 8000000UL
#include <util/delay.h>

#define BAUD 9600
#include <util/setbaud.h>

FUSES =
{
    .low = (LFUSE_DEFAULT),
    .high = (HFUSE_DEFAULT),
};

// definitions/macros:
#define SET_FLAG(x) (g_flags|=(x))
#define CLEAR_FLAG(x) (g_flags&=~(x))
#define TOGGLE_FLAG(x) (g_flags^=(x))
#define FLAG_IS_SET(x) (g_flags&(x))
#define FLAG_IS_CLEAR(x) (~g_flags&(x))
#define MAXOF(x,y) (((x)>(y))?(x):(y))
#define MINOF(x,y) (((x)<(y))?(x):(y))

// structs:
typedef struct _clock_time
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t day;
  uint8_t month;
  uint8_t year;
} clock_time;

// function prototypes:
void get_i2c_time(void);

// global variables:
clock_time g_ctime;

// eeprom variables:

// main:
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

ISR(INT1_vect)
{

}

// functions:

void
get_i2c_time(void)
{

}
