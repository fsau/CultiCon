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

#ifndef pins_defs_header
#define pins_defs_header

#define F_CPU 8000000UL
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

#endif
