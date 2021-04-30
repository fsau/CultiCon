#ifndef lcdmenus_h_header
#define lcdmenus_h_header

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "pins-defs.h"

#define LINE_SIZE 16
#define LINE_N 2
#define INPUT_N 4

typedef enum lcd_input_e
{
  input_none=0, input_home=1, input_ok=2, input_incr=4, input_decr=8,
} LCDInput;

enum lcd_node_type_e
{
  node_null=0, node_print_Pstr, node_print_memstr, node_print_hhmm,
  node_print_hhmmss, node_print_temp, node_print_perc, node_edit_hhmm,
  node_edit_hhmmss, node_edit_temp, node_edit_perc, node_set_menu,
};

typedef struct _lcd_node_s LCDNode;

union lcd_pointer_u
{
  const LCDNode* const *n;
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
