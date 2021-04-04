#include <avr/io.h>

#define LINE_SIZE 16
#define LINE_N 2

typedef enum _lcd_input_e
{
  lcd_input_none=0, lcd_input_home, lcd_input_ok, lcd_input_incr, lcd_input_decr,
} LCDInput;

typedef struct _lcd_context_s
{
  PGM_P *string;
  const uint8_t *arg;
} LCDDisp;

// Public functions:

void lcd_init(void);
void lcd_update(void);
void lcd_refresh(void);
void lcd_input(LCDInput);

// Application specific:

extern void lcd_send_data(uint8_t, uint8_t);
