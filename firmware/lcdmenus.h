#define LINE_SIZE 16
#define LINE_N 2
#define INPUT_SW_N 3

typedef enum _lcd_mode_e
{
  lcd_off=0, lcd_main, lcd_settings, lcd_edit_num, lcd_edit_time, lcd_edit_bit,
  lcd_debug,
} LCDMode;

typedef struct _lcd_context_s
{
  LCDDisp disp;
  uint8_t *arg;
} LCDContext;

typedef const LCDContext[] PROGMEM LCDMenu;

LCDMenu main_menu =
{
  {.disp=lcd_main,.arg=NULL},
  {.disp=lcd_settings,.arg=NULL},
  {.disp=lcd_edit,.arg=NULL},
};

extern void lcd_send_data(uint8_t, uint8_t);
void lcd_init(void);
void lcd_update(void);
void lcd_clear(void);
