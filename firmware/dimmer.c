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

#include "dimmer.h"

#define FLAG_NEXT_CYCLE _BV(0)

uint8_t currtask_n = 0;
cnt_uint last_sync;
uint8_t iflags=0;

struct _chrono_task
{
  cnt_uint delta; // 0 to 255: 0-100%
  uint8_t func;
} tasks[TASKS_N];

// functions:

uint8_t
ext_sync(cnt_uint curr_time)
{
  cnt_uint period = curr_time - last_sync;
  if(period>=g_mean_per-PER_MAX_DELTA/2)
  {
    g_mean_per = (7*(cnt_long)g_mean_per + period + 3)/8; // update p
    last_sync = curr_time;
    iflags&=~FLAG_NEXT_CYCLE;
    return 1;
  }
  return 0;
}

void
load_next_task(void)
{
  uint8_t nexttask;

  do
  {
    nexttask = (currtask_n+1)%TASKS_N;
  } while(!tasks[nexttask].func&&(nexttask!=currtask_n));

  currtask_n = nexttask;

  if(currtask_n==0)
  {
    iflags |= FLAG_NEXT_CYCLE;
  }
}

uint8_t
get_curr_func(void)
{
  return tasks[currtask_n].func;
}

cnt_uint
get_curr_cmp(void)
{
  cnt_uint next_cmp = last_sync +
          (g_mean_per*(cnt_long)tasks[currtask_n].delta)/256l;

  if(iflags&&FLAG_NEXT_CYCLE)
  {
    next_cmp += g_mean_per;
  }

  return next_cmp;
}

void
load_onoff_tasks(cnt_uint deltaON, cnt_uint deltaOFF)
{
  if(deltaON > deltaOFF)
  {
    tasks[0].delta = deltaOFF;
    tasks[0].func = 1;

    tasks[1].delta = deltaON;
    tasks[1].func = 2;
  }
  else
  {
    tasks[0].delta = deltaON;
    tasks[0].func = 2;

    tasks[1].delta = deltaOFF;
    tasks[1].func = 1;
  }
}
