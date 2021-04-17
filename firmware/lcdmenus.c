#include "lcdmenus.h"
#include "strings.c"

// Private functions:
uint8_t
lcd_read_node(const LCDNode* nodetp)
{
  uint8_t endnode=0;

  switch(nodetp.type)
  {
    case node_print_Pstr:
      break;
    case node_print_vstr:
      break;
    case node_print_hhmm:
      break;
    case node_print_hhmmss:
      break;
    case node_print_temp:
      break;
    case node_print_perc:
      break;
    case node_edit_hhmm:
      break;
    case node_edit_hhmmss:
      break;
    case node_edit_temp:
      break;
    case node_edit_perc:
      break;
    case node_set_menu:
      break;
    default:
    case node_null:
      break;
  }
  
  return endnode;
}
