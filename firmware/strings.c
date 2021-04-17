const uint8_t str_culticn[] PROGMEM = "CultiCon v0.1";
const uint8_t str_inicial[] PROGMEM = "Inicializando...";
const LCDNode print_init[] PROGMEM =
{
  {.arg=0;.type=node_print_Pstr,.ptr.s=str_culticn},
  {.arg=LINE_SIZE;.type=node_print_Pstr,.ptr.s=str_inicial},
  {.type=node_null},
};

const uint8_t str_stson[] PROGMEM  = "Ligado";
const uint8_t str_stsoff[] PROGMEM = "Desligado";
const uint8_t str_degc[] PROGMEM = "°C";
const uint8_t str_perc[] PROGMEM = "%rh";
*g_status_string = &str_stsoff;
const LCDNode print_main[] PROGMEM =
{
  {.arg=0;.type=node_print_vstr,.ptr.v=g_status_string},
  {.arg=10;.type=node_print_hhmm,.ptr.v=&g_curr_time},
  {.arg=LINE_SIZE;.type=node_print_temp,.ptr.v=&g_dtemp},
  {.arg=LINE_SIZE+9;.type=node_print_perc,.ptr.v=&g_dtemp},
  {.arg=LINE_SIZE+3;.type=node_print_Pstr,.ptr.s=str_degc},
  {.arg=LINE_SIZE+13;.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=0;.type=node_set_menu,.ptr.s=&disp_menu},
};

const uint8_t str_menuhr[] PROGMEM  = "Horário atual";
const LCDNode print_menuhr[] PROGMEM =
{
  {.arg=0;.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=LINE_SIZE+9;.type=node_print_hhmmss,.ptr.v=&g_curr_time},
  {.arg=LINE_SIZE+9;.type=node_edit_hhmmss,.ptr.v=&g_curr_time},
};

const uint8_t str_timeon[] PROGMEM  = "Ligar às";
const LCDNode print_timeon[] PROGMEM =
{
  {.arg=0;.type=node_print_Pstr,.ptr.s=str_timeon},
  {.arg=LINE_SIZE+11;.type=node_print_hhmm,.ptr.v=&g_timer_on},
  {.arg=LINE_SIZE+11;.type=node_edit_hhmm,.ptr.v=&g_timer_on},
};

const uint8_t str_timeoff[] PROGMEM  = "Desligar às";
const LCDNode print_timeoff[] PROGMEM =
{
  {.arg=0;.type=node_print_Pstr,.ptr.s=str_timeoff},
  {.arg=LINE_SIZE+11;.type=node_print_hhmm,.ptr.v=&g_timer_off},
  {.arg=LINE_SIZE+11;.type=node_edit_hhmm,.ptr.v=&g_timer_off},
};

const uint8_t str_dimon[] PROGMEM  = "% dimmer dia";
const LCDNode print_dimon[] PROGMEM =
{
  {.arg=0;.type=node_print_Pstr,.ptr.s=str_dimon},
  {.arg=LINE_SIZE+9;.type=node_print_perc,.ptr.v=&g_dimmer_on},
  {.arg=LINE_SIZE+13;.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=LINE_SIZE+9;.type=node_edit_perc,.ptr.v=&g_dimmer_on},
};

const uint8_t str_dimoff[] PROGMEM  = "% dimmer noite";
const LCDNode print_dimoff[] PROGMEM =
{
  {.arg=0;.type=node_print_Pstr,.ptr.s=str_dimoff},
  {.arg=LINE_SIZE+9;.type=node_print_perc,.ptr.v=&g_dimmer_off},
  {.arg=LINE_SIZE+13;.type=node_print_Pstr,.ptr.s=str_perc},
  {.arg=LINE_SIZE+9;.type=node_edit_perc,.ptr.v=&g_dimmer_off},
};

const uint8_t str_tcrit[] PROGMEM  = "Temp. crítica";
const LCDNode print_tcrit[] PROGMEM =
{
  {.arg=0;.type=node_print_Pstr,.ptr.s=str_tcrit},
  {.arg=LINE_SIZE+9;.type=node_print_temp,.ptr.v=&g_crtemp},
  {.arg=LINE_SIZE+14;.type=node_print_Pstr,.ptr.s=str_degc},
  {.arg=LINE_SIZE+9;.type=node_edit_temp,.ptr.v=&g_crtemp},
};

const LCDNode* disp_menu[] PROGMEM =
{
  print_menuhr, print_timeon, print_timeoff, print_dimon, print_dimoff,
  print_tcrit,
}
