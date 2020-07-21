#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/cpufunc.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <util/setbaud.h>

// useful macros:
#define SET_FLAG(x) (g_flags|=(x))
#define CLEAR_FLAG(x) (g_flags&=~(x))
#define TOGGLE_FLAG(x) (g_flags^=(x))
#define FLAG_IS_SET(x) (g_flags&(x))
#define FLAG_IS_CLEAR(x) (~g_flags&(x))
#define MAXOF(x,y) (((x)>(y))?(x):(y))
#define MINOF(x,y) (((x)<(y))?(x):(y))

FUSES =
{
    .low = (LFUSE_DEFAULT),
    .high = (HFUSE_DEFAULT),
};

// structs:
typedef struct _clock_time
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} clock_time;
