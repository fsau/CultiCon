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

typedef struct _lcd_node_s LCDNode;

extern const LCDNode *print_main_v, *print_init_v, *str_stson_v,
                     *str_stsoff_v;

// Public functions:

void lcd_init(void);
void lcd_refresh(void);
void lcd_input(LCDInput);

// Application specific:

extern void lcd_send_data(uint8_t rs, uint8_t data);
