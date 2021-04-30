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

#ifndef main_menu_h_header
#define main_menu_h_header

#include "lcdmenus.h"

// Externally defined interface
extern PGM_P *g_status_string;
extern RTCtime *g_curr_time;
extern RTCtime *g_timer_on;
extern RTCtime *g_timer_off;
extern fp_t *g_dtemp;
extern fp_t *g_crtemp;
extern fp_t *g_dhumd;
extern fp_t *g_dimmer_on;
extern fp_t *g_dimmer_off;

// Internal variables
extern const LCDNode *print_init_v;
extern const char *str_stson_v;
extern const char *str_stsoff_v;

#endif
