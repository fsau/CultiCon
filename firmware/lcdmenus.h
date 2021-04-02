#include <avr/io.h>

#define LINE_SIZE 16
#define LINE_N 2

typedef enum _lcd_mode_e
{
  lcd_off=0, lcd_main, lcd_menu, lcd_edit, lcd_debug,
} LCDMode;

typedef enum _lcd_argtype_e
{
  arg_null=0, arg_temp, arg_time, arg_num, arg_bit,
} LCDArgType;

typedef enum _lcd_input_e
{
  lcd_input_none=0, lcdinput_back=1, lcd_input_incr=2, lcd_input_decr=4,
} LCDInput;

typedef struct _lcd_context_s
{
  LCDDisp disp;
  PGM_P *string;
  LCDArgType type;
  void *arg;
} LCDContext;



// Public functions:

void lcd_init(void);
void lcd_update(void);
void lcd_refresh(void);
void lcd_input(LCDInput);

// Application specific:

extern void lcd_send_data(uint8_t, uint8_t);
