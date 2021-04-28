
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
