typedef enum _lcd_node_type_e
{
  lcd_node_null=0, lcd_pgmstr, lcd_pgmjmp, lcd_ptr, lcd_fun, lcd_uintv, lcd_cmd,
} nodeType;

typedef union _lcd_node_data_u
{
  void *vptr;
  PGM_P pptr;
  void *fptr(void*);
  uint8_t uint[3];
} nodeData;

typedef struct _lcd_node_s
{
  nodeType type;
  nodeData data;
} Node;

// Global variables:

PGM_P inputs_ptr[INPUT_N];

// Strings:

uint8_t str_culticn[] PROGMEM = "CultiCon";
uint8_t str_inicial[] PROGMEM = "Inicializando...";
uint8_t str_ajusthr[] PROGMEM = "Horário atual";
uint8_t str_ajuston[] PROGMEM = "Horário ON";
uint8_t str_ajusoff[] PROGMEM = "Horário OFF";
uint8_t str_ajusdon[] PROGMEM = "% dimmer ON";
uint8_t str_ajudoff[] PROGMEM = "% dimmer OFF";
uint8_t str_ajustcr[] PROGMEM = "Temp. crítica";

Node main_menu[] PROGMEM =
{
  {.type=lcd_pgmstr,.data=&str_culticn},
  {.type=lcd_pgmstr,.data=&str_inicial},
  {.type=lcd_node_null};
}
