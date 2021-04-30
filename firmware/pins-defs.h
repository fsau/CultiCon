#define F_CPU 8000000
#include <util/delay.h>

// Generic time-of-day data structure (second resolution)
typedef struct _rtc_time_s
{
  uint8_t h;
  uint8_t m;
  uint8_t s;
} RTCtime;

// Fixed point type for "real" numbers:
typedef int16_t fp_t;
typedef int32_t longfp_t;
#define FP_FRACTIONAL_BITS 6
#define FP_ONE (1<<FP_FRACTIONAL_BITS)
#define FP_MAX_VAL INT16_MAX

// lcdmenus memory interface:
extern PGM_P *g_status_string;
extern RTCtime *g_curr_time;
extern RTCtime *g_timer_on;
extern RTCtime *g_timer_off;
extern fp_t *g_dtemp;
extern fp_t *g_crtemp;
extern fp_t *g_dhumd;
extern fp_t *g_dimmer_on;
extern fp_t *g_dimmer_off;
