// Global variables:

LCDContext lcd_status;

// Functions:

void lcd_update()
{
  switch(lcd_status.disp)
  {
    case lcd_main:
      break;
    case lcd_menu:
      break;
    case lcd_edit:
      break;
    case lcd_debug:
      break;
    default:
    case lcd_off:
      break;
  }
}

void lcd_input(LCDInput)
{
  switch(lcd_status.disp)
  {
    case lcd_main:
      break;
    case lcd_menu:
      break;
    case lcd_edit:
      break;
    case lcd_debug:
      break;
    default:
    case lcd_off:
      break;
  }
}
