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

#include "main-menu.h"

const char str_culticn[] PROGMEM = "CultiCon v0.1";
const char str_inicial[] PROGMEM = "Inicializando...";
const char str_menuhr[] PROGMEM  = "Horário atual";
const char str_timeon[] PROGMEM  = "Ligar às";
const char str_timeoff[] PROGMEM  = "Desligar às";
const char str_dimon[] PROGMEM  = "% dimmer dia";
const char str_dimoff[] PROGMEM  = "% dimmer noite";
const char str_tcrit[] PROGMEM  = "Temp. crítica";
const char str_stson[] PROGMEM  = "Ligado";
const char str_stsoff[] PROGMEM = "Desligado";
const char str_degc[] PROGMEM = "°C";
const char str_perc[] PROGMEM = "%rh";

// PGM_P *g_status_string=NULL;
// RTCtime *g_curr_time=NULL;
// RTCtime *g_timer_on=NULL;
// RTCtime *g_timer_off=NULL;
// fp_t *g_dtemp=NULL;
// fp_t *g_crtemp=NULL;
// fp_t *g_dhumd=NULL;
// fp_t *g_dimmer_on=NULL;
// fp_t *g_dimmer_off=NULL;

const LCDNode print_menuhr[] PROGMEM =
{
  {.arg=0,.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=LINE_SIZE+9,.type=node_print_hhmmss,.ptr.v=&g_curr_time},
  {.arg=LINE_SIZE+9,.type=node_edit_hhmmss,.ptr.v=&g_curr_time},
};

const LCDNode print_timeon[] PROGMEM =
{
  {.arg=0,.type=node_print_Pstr,.ptr.s=str_timeon},
  {.arg=LINE_SIZE+11,.type=node_print_hhmm,.ptr.v=&g_timer_on},
  {.arg=LINE_SIZE+11,.type=node_edit_hhmm,.ptr.v=&g_timer_on},
};

const LCDNode print_timeoff[] PROGMEM =
{
  {.arg=0,.type=node_print_Pstr,.ptr.s=str_timeoff},
  {.arg=LINE_SIZE+11,.type=node_print_hhmm,.ptr.v=&g_timer_off},
  {.arg=LINE_SIZE+11,.type=node_edit_hhmm,.ptr.v=&g_timer_off},
};

const LCDNode print_dimon[] PROGMEM =
{
  {.arg=0,.type=node_print_Pstr,.ptr.s=str_dimon},
  {.arg=LINE_SIZE+9,.type=node_print_perc,.ptr.v=&g_dimmer_on},
  {.arg=LINE_SIZE+13,.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=LINE_SIZE+9,.type=node_edit_perc,.ptr.v=&g_dimmer_on},
};

const LCDNode print_dimoff[] PROGMEM =
{
  {.arg=0,.type=node_print_Pstr,.ptr.s=str_dimoff},
  {.arg=LINE_SIZE+9,.type=node_print_perc,.ptr.v=&g_dimmer_off},
  {.arg=LINE_SIZE+13,.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=LINE_SIZE+9,.type=node_edit_perc,.ptr.v=&g_dimmer_off},
};

const LCDNode print_tcrit[] PROGMEM =
{
  {.arg=0,.type=node_print_Pstr,.ptr.s=str_tcrit},
  {.arg=LINE_SIZE+9,.type=node_print_temp,.ptr.v=&g_crtemp},
  {.arg=LINE_SIZE+14,.type=node_print_Pstr,.ptr.s=str_degc},
  {.arg=LINE_SIZE+9,.type=node_edit_temp,.ptr.v=&g_crtemp},
};

const LCDNode* const disp_menu[] PROGMEM =
{
  print_menuhr, print_timeon, print_timeoff, print_dimon, print_dimoff,
  print_tcrit,
};
#define menu_len (sizeof(disp_menu)/sizeof(const LCDNode*))

const LCDNode print_main[] PROGMEM =
{
  {.arg=0,.type=node_print_memstr,.ptr.v=&g_status_string},
  {.arg=10,.type=node_print_hhmm,.ptr.v=&g_curr_time},
  {.arg=LINE_SIZE,.type=node_print_temp,.ptr.v=&g_dtemp},
  {.arg=LINE_SIZE+9,.type=node_print_perc,.ptr.v=&g_dtemp},
  {.arg=LINE_SIZE+3,.type=node_print_Pstr,.ptr.s=str_degc},
  {.arg=LINE_SIZE+13,.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=menu_len,.type=node_set_menu,.ptr.n=disp_menu},
};

const LCDNode print_init[] PROGMEM =
{
  {.arg=0,.type=node_print_Pstr,.ptr.s=str_culticn},
  {.arg=LINE_SIZE,.type=node_print_Pstr,.ptr.s=str_inicial},
  {.arg=0,.type=node_goto_mode,.ptr.m=print_main},
};

const LCDNode *print_init_v=print_init;
const char *str_stson_v=str_stson;
const char *str_stsoff_v=str_stsoff;
