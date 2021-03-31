#ifndef DIMMER_H_BLOCK
#define DIMMER_H_BLOCK

#include <avr/io.h>

// definitions:

#define TASKS_N 2
#define PER_MAX_DELTA 20

typedef uint8_t cnt_uint;
typedef uint16_t cnt_long;

// typedef struct _chrono_task * Task;

// variables:

extern cnt_uint g_mean_per;

// functions:

uint8_t ext_sync(cnt_uint);
uint8_t get_curr_func(void);
cnt_uint get_curr_cmp(void);
void load_next_task(void);
void load_onoff_tasks(cnt_uint, cnt_uint);

#endif
