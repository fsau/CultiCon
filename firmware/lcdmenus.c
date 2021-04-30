#include "lcdmenus.h"

#define NULL (void*)0

// Private/internal variables:
const LCDNode *cmode_node=NULL, *cinput_node, *cmenu_node;
LCDInput input_flags=0;
uint8_t menu_state;

// Private functions:
void
set_pos(uint8_t pos)
{
  uint8_t line = pos/LINE_SIZE;
  int8_t offset = 0;
  switch(line)
  {
    default:
    case 0: offset = 0; break;
    case 1: offset = 64; break;
    case 2: offset = 20; break;
    case 3: offset = 84; break;
  }
  lcd_send_data(0,0x80 + offset + (pos%LINE_SIZE));
}

void
print_memstr(uint8_t pos, char *str)
{
  uint8_t i = 0;
  char cts = str[0];

  if(pos!=0xFF) set_pos(pos);

  do
  {
    if(!((pos+i)%LINE_SIZE)) set_pos(pos+i);
    lcd_send_data(1,cts);
    i++;
    cts = str[i];
  }
  while(cts);
}

void
print_Pstr(uint8_t pos, PGM_P str)
{
  uint8_t i = 0;
  char cts = pgm_read_byte(&str[0]);

  if(pos!=0xFF) set_pos(pos);

  do
  {
    if(!((pos+i)%LINE_SIZE)) set_pos(pos+i);
    lcd_send_data(1,cts);
    i++;
    cts = pgm_read_byte(&str[i]);
  }
  while(cts);
}

uint8_t
num2str(char str[], uint16_t num, uint8_t slen)
{
  for(uint8_t i = 1; i <= slen; i++)
  {
    uint8_t dec = num%10;
    str[slen - i] = '0' + dec;
    num /= 10;
    if(num==0) break;
  }
  return num;
}

uint16_t
pow10e(uint8_t pow)
{
  uint16_t ret;
  switch(pow)
  {
    case 0: ret=1l; break;
    case 1: ret=10l; break;
    case 2: ret=100l; break;
    case 3: ret=1000l; break;
    case 4: ret=10000l; break;
    default: ret=1l; break;
  }
  return ret;
}

void
print_rtctime(uint8_t pos, RTCtime *time, uint8_t opt)
{
  char buf[2];
  num2str(buf, time->h, 2);
  print_memstr(pos,buf);
  lcd_send_data(1,':');
  num2str(buf, time->m, 2);
  print_memstr(0xFF,buf);

  if(opt&0x01)
  {
    lcd_send_data(1,':');
    num2str(buf, time->s, 2);
    print_memstr(0xFF,buf);
  }
}

enum pnum_opts
{
  pnum_default=0,
  pnum_onlypos=1, // crop to 0~inf
  pnum_int=2, // use no frac bit
  pnum_perc=4, // crop to 0~100
  pnum_rlead0=8, // remove leading 0s
  pnum_pmsgn=16, // print +/- sign
  pnum_abs=32, // ignore sign
  pnum_halfp=64, // use half the frac bits for large numbers
};

void
print_num(uint8_t pos, fp_t num, uint8_t int_n, uint8_t frac_n,
  enum pnum_opts options)
{
  char str_int[int_n], str_frac[frac_n];
  uint8_t nsgn = 0;

  if((num<0))
  {
    if(options & pnum_onlypos)
    {
      num = 0;
    }
    else
    {
      num *= -1; // keep abs value
    }
    nsgn = 1;
  }

  if((options & pnum_perc))
  {
    if(nsgn)
    {
      num = 0;
    }
    else if(num > 100*FP_ONE)
    {
      num = 100*FP_ONE;
    }
    nsgn=0;
  }

  uint16_t num_frac, num_int;

  if(options & pnum_int)
  {
    num_int = num;
    num_frac = 0;
  }
  else if(options & pnum_halfp)
  {
    num+=FP_ONE/pow10e(frac_n)/4; // correct rounding
    num_int = num>>(FP_FRACTIONAL_BITS/2);
    num -= num_int<<(FP_FRACTIONAL_BITS/2);
    num_frac = (pow10e(frac_n)*num)>>(FP_FRACTIONAL_BITS/2);
  }
  else
  {
    num+=FP_ONE/pow10e(frac_n)/2; // correct rounding
    num_int = num>>FP_FRACTIONAL_BITS;
    num -= num_int<<FP_FRACTIONAL_BITS;
    num_frac = (pow10e(frac_n)*num)>>FP_FRACTIONAL_BITS;
  }

  num2str(str_int, num_int, int_n);
  num2str(str_frac, num_frac, frac_n);

  if(pos!=0xFF) set_pos(pos);

  for(uint8_t i = 0, lead0 = 1;i<int_n;i++)
  {
    if((options&pnum_rlead0) && lead0 && (str_int[i]=='0') && (i<(int_n-1)))
    {
      lcd_send_data(1,' ');
    }
    else
    {
      if(lead0 && (options & pnum_pmsgn))
      {
        lcd_send_data(1,(nsgn)?'-':'+');
      }
      else
      {
        if(~options & pnum_abs) lcd_send_data(1,(nsgn)?'-':' ');
      }
      lead0=0;

      lcd_send_data(1,str_int[i]);
    }
  }

  if(!(options & pnum_int)&&frac_n)
  {
    lcd_send_data(1,'.');
  }

  for(uint8_t i = 0; i<frac_n; i++)
  {
    lcd_send_data(1,str_frac[i]);
  }
}

void
update_menu(const LCDNode* const menu_table[])
{
  switch(input_flags)
  {
    case input_ok:
      break;
    case input_incr:
      menu_state++;
      if(pgm_read_ptr(menu_table[menu_state])==NULL) menu_state--;
        cmode_node=pgm_read_ptr(menu_table[menu_state]);
      break;
    case input_decr:
      if(menu_state) menu_state--;
      cmode_node=pgm_read_ptr(menu_table[menu_state]);
      break;
    case input_home:
    case input_none:
    default:
      break;
  }
  input_flags=input_none;
}

// Node functions:

uint8_t
print_node(const LCDNode* nodetp)
{
  uint8_t carry=0;
  LCDNode lnode;
  memcpy_P(&lnode, nodetp, sizeof(lnode));

  switch(lnode.type)
  {
    case node_print_Pstr:
      print_Pstr(lnode.arg, lnode.ptr.s);
      break;
    case node_print_memstr:
      print_memstr(lnode.arg, lnode.ptr.v);
      break;
    case node_print_hhmmss:
      carry|=1;
    case node_print_hhmm:
      print_rtctime(lnode.arg, (RTCtime*)lnode.ptr.v, carry&1);
      break;
    case node_print_temp:
      print_num(lnode.arg, *(fp_t*)lnode.ptr.v, 2, 1, pnum_default);
      break;
    case node_print_perc:
      print_num(lnode.arg, *(fp_t*)lnode.ptr.v, 2, 0, pnum_perc);
      break;
    case node_set_menu:
      cmenu_node = nodetp;
    case node_edit_hhmmss:
    case node_edit_hhmm:
    case node_edit_temp:
    case node_edit_perc:
      carry|=2;
      cinput_node = nodetp;
    default:
      break;
  }

  return carry&2;
}

void
input_node(const LCDNode* inPnode)
{
  LCDNode innode;
  memcpy_P(&innode, inPnode, sizeof(innode));

  switch(innode.type)
  {
    case node_set_menu:
      update_menu(innode.ptr.n);
      break;
    case node_edit_hhmmss:
    case node_edit_hhmm:
    case node_edit_temp:
    case node_edit_perc:
    default:
    break;
  }
}

void
read_mode(const LCDNode* mode)
{
  while(print_node(mode++)==0);
}

// Public functions:

void
lcd_init(LCDNode *init)
{
  lcd_send_data(0,0x00);

  _delay_ms(150);

  lcd_send_data(0,0x30);
  _delay_ms(8);
  lcd_send_data(0,0x30);
  _delay_ms(8);
  lcd_send_data(0,0x30);
  _delay_ms(8);

  lcd_send_data(0,0x20); // 4 bit
  _delay_ms(5);
  lcd_send_data(0, 0x28); // 4 bit/2 line
  _delay_ms(5);
  lcd_send_data(0, 0x08); // display off
  _delay_ms(5);
  lcd_send_data(0, 0x01); // clear ram
  _delay_ms(5);
  lcd_send_data(0, 0x02); // return home
  _delay_ms(5);
  lcd_send_data(0, 0x06); // auto increment, no shift

  // // Load CGRAM for special characters:
  // for(uint8_t k = 0; k < INIT_STR_SIZE; k++)
  // {
  //   lcd_send_data(0,0x40+k); // set cgaddr = 0;
  //   lcd_send_data(1, pgm_read_byte(&special_c[k])-'F');
  // }

  _delay_ms(5);
  lcd_send_data(0, 0x0C); // display on, cursor off


}

void
lcd_input(LCDInput input)
{
  input_flags |= input;
}

void
lcd_refresh(void)
{
  read_mode(cmode_node);
}
