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

#ifndef lcdmenus_h_header
#define lcdmenus_h_header

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include "pins-defs.h"

#define LINE_SIZE 16
#define LINE_N 2
#define INPUT_N 4

typedef enum lcd_input_e
{
  input_none=0, input_cancel=1, input_select=2, input_up=4, input_down=8,
} LCDInput;

enum lcd_node_type_e
{
  node_null=0, node_print_Pstr, node_print_memstr, node_print_hhmm,
  node_print_hhmmss, node_print_temp, node_print_perc, node_edit_hhmm,
  node_edit_hhmmss, node_edit_temp, node_edit_perc, node_set_menu,
  node_goto_mode,
};

typedef struct _lcd_node_s LCDNode;

union lcd_pointer_u
{
  const LCDNode* const *n;
  const LCDNode* m;
  const char *s;
  void *v;
};

typedef struct _lcd_node_s
{
  enum lcd_node_type_e type;
  union lcd_pointer_u ptr;
  uint8_t arg;
} LCDNode;

// Public functions:
void lcd_init(LCDNode*);
void lcd_refresh(void);
void lcd_input(LCDInput);

// Application specific:
extern void lcd_send_data(uint8_t rs, uint8_t data);

#endif
