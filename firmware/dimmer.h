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
