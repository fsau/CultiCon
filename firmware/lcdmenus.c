#include "lcdmenus.h"
#include "strings.c"

// Private/internal variables:

LCDNode *cmode_node, *cinput_node;

// Private functions:

void
load_node(const LCDNode* nodetp)
{
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
    case node_edit_hhmmss:
    case node_edit_temp:
    case node_edit_perc:
    case node_set_menu:
      cinput_node=nodetp;
      break;
    default:
      break;
  }
}

uint8_t
is_node_final(const LCDNode* node)
{
  uint8_t final=1;

  switch(node.type)
  {
    case node_print_Pstr:
    case node_print_vstr:
    case node_print_hhmm:
    case node_print_hhmmss:
    case node_print_temp:
    case node_print_perc:
      final=0;
    default:
      break;
  }

  return final;
}

void
read_mode(const LCDNode* mode)
{
  do
  {
    load_node(mode);
  } while(!is_node_final(mode++));
}

// Public functions:

void
lcd_input(LCDInput input)
{
  switch(cinput_node.type)
  {
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
      break;
  }
}

void
lcd_refresh(void)
{
  read_mode(cmode_node);
}
