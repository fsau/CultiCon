#include "lcdmenus.h"
#include "main-menu.c"

// Private/internal variables:

LCDNode *cmode_node, *cinput_node;

// Private functions:

void
set_pos(uint8_t pos)
{
  uint8_t line = pos/SIZE_LINE;
  int8_t offset = 0;
  switch(line)
  {
    default:
    case 0: offset = 0; break;
    case 1: offset = 64; break;
    case 2: offset = 20; break;
    case 3: offset = 84; break;
  }
  lcd_send_data(0,0x80 + offset + (pos%SIZE_LINE));
}

void
print_vstr(uint8_t pos, char *str)
{
  uint8_t i = 0;
  char cts = str[0];

  set_pos(pos);

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
print_Pstr(uint8_t pos, PGR_P str)
{
  uint8_t i = 0;
  char cts = pgm_read_byte(&str[0]);

  set_pos(pos);

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
  uint8_t buf[2];
  set_pos(pos);
  num2str(buf, time->h, 2);
  print_vstr(buf);
  lcd_send_data(1,':');
  num2str(buf, time->m, 2);
  print_vstr(buf);

  if(opt&0x01)
  {
    lcd_send_data(1,':');
    num2str(buf, time->s, 2);
    print_vstr(buf);
  }
}

enum pnum_opts
{
  pnum_default=0,
  pnum_onlypos=1, // crop to 0~inf
  pnum_int=2, // use no frac bit
  pnum_perc=4, // crop to 0~100
  pnum_rlead0=8, // remove leading 0's
  pnum_pmsgn=16, // print + sign
  pnum_abs=32, // never print - sign
  pnum_halfp=64, // use half the frac bits
};

void
print_num(uint8_t pos, uint16_t num, uint8_t int_n, uint8_t frac_n,
  enum pnum_opts options)
{
  char str_int[int_n], str_frac[frac_n];
  uint8_t nsgn = 0;

  if(num<0)
  {
    nsgn = 1;
    if(options & pnum_onlypos)
    {
      num = 0;
    }
    else
    {
      num *= -1;
    }
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

  if((options & pnum_perc))
  {
    if(nsgn)
    {
      num_int = 0;
      num_frac = 0;
    }
    else if(num_int > 100)
    {
      num_int = 100;
      num_frac = 0;
    }
    nsgn=0;
  }

  num2str(str_int, num_int, int_n);
  num2str(str_frac, num_frac, frac_n);

  set_pos(pos);

  if(options & pnum_pmsgn)
  {
    lcd_send_data(1,(nsgn)?'-':'+');
  }
  else if(!(options & pnum_abs) && nsgn)
  {
    lcd_send_data(1,'-');
  }

  uint8_t k = 0, lead0 = 1;
  while(k<int_n)
  {
    if((options&pnum_rlead0) && lead0 && (str_int[k]=='0') && (k<(int_n-1)))
    {
      lcd_send_data(1,' ');
    }
    else
    {
      lead0=0;
      lcd_send_data(1,str_int[k]);
    }
    k++;
  }

  if(!(options & pnum_int))
  {
    lcd_send_data(1,'.');
  }

  k = 0;
  while((k<frac_n))
  {
    lcd_send_data(1,str_frac[k]);
    k++;
  }
}

// Node functions:

void
load_node(const LCDNode* nodetp)
{
  LCDNode lnode;
  memcpy_P(&lnode, nodetp, sizeof(lnode));
  uint8_t zero=0;

  switch(lnode.type)
  {
    case node_print_Pstr:
      print_Pstr(lnode.arg, lnode.ptr.s);
      break;
    case node_print_vstr:
      print_vstr(lnode.arg, lnode.ptr.v);
      break;
    case node_print_hhmmss:
      zero=1;
    case node_print_hhmm:
      RTCtime *time = lnode.ptr.v;
      print_rtctime(lnode.arg, time, zero);
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
lcd_init(void)
{
  lcd_send_data(0,0x00);

  long_delay(0);

  lcd_send_data(0,0x30);
  long_delay(1);
  lcd_send_data(0,0x30);
  long_delay(1);
  lcd_send_data(0,0x30);
  long_delay(1);

  lcd_send_data(0,0x20);

  long_delay(2);
  lcd_send_data(0, 0x28); // 4 bit/2 line
  long_delay(2);
  lcd_send_data(0, 0x08); // display off
  long_delay(2);
  lcd_send_data(0, 0x01); // clear ram
  long_delay(2);
  lcd_send_data(0, 0x02); // return home
  long_delay(2);
  lcd_send_data(0, 0x06); // auto increment, no shift

  // // Load CGRAM for special characters:
  // for(uint8_t k = 0; k < INIT_STR_SIZE; k++)
  // {
  //   lcd_send_data(0,0x40+k); // set cgaddr = 0;
  //   lcd_send_data(1, pgm_read_byte(&special_c[k])-'F');
  // }

  long_delay(2);
  lcd_send_data(0, 0x0C); // display on, cursor off
}

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
