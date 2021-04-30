#ifndef main_menu_h_header
#define main_menu_h_header

#include "lcdmenus.h"

// Memory interface:
extern const LCDNode *print_init_v;
extern const char *str_stson_v;
extern const char *str_stsoff_v;
extern PGM_P *g_status_string;
extern RTCtime *g_curr_time;
extern RTCtime *g_timer_on;
extern RTCtime *g_timer_off;
extern fp_t *g_dtemp;
extern fp_t *g_crtemp;
extern fp_t *g_dhumd;
extern fp_t *g_dimmer_on;
extern fp_t *g_dimmer_off;

#endif
