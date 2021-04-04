#include <avr/io.h>

#define LINE_SIZE 16
#define LINE_N 2
#define INPUT_N 3

typedef enum _lcd_input_e
{
  lcd_input_none=0, lcdinput_back=1, lcd_input_incr=2, lcd_input_decr=4,
} LCDInput;




// Public functions:

void lcd_init(void);
void lcd_update(void);
void lcd_refresh(void);
void lcd_input(LCDInput);

// Application specific:

extern void lcd_send_data(uint8_t, uint8_t);
