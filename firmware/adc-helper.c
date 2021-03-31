uint16_t
adc_get(uint8_t admux_chan)
{
  ADMUX = ADMUX_DEFAULT|admux_chan;
  ADCSRA |= _BV(ADSC); // start conversion
  loop_until_bit_is_set(ADCSRA, ADIF); // wait until complete
  ADCSRA |= _BV(ADIF); // clear adc interrupt flag
  return ADC;
}

uint8_t
adc_quantify(uint16_t raw, uint8_t old, uint8_t qnt, uint8_t hyst)
{
  if(raw < ADC_POTMIN) raw = ADC_POTMIN; // lower limit
  else if(raw >= ADC_POTMAX) raw = ADC_POTMAX-1; // upper limit
  raw -= ADC_POTMIN;

  uint8_t delta = ADC_POTDELTA/qnt + 1;
  uint8_t new = raw/delta;

  if( ((new > old) && ((raw - delta*(old+1)) > hyst)) ||
      ((new < old) && ((delta*old - raw) > hyst)) )
  {
    return new;
  }
  else
  {
    return old;
  }
}

uint8_t
adc_quantify_table(uint16_t raw,uint8_t old, uint8_t table_size, uint8_t hyst,
  const uint16_t comp_table[])
{
  uint8_t new = 0;

  while(raw > pgm_read_word(&comp_table[new]))
  {
    new++;
    if(new==table_size) break;
  }

  if( ((new > old) && ((raw - pgm_read_word(&comp_table[old+1])) > hyst)) ||
      ((new < old) && ((pgm_read_word(&comp_table[old]) - raw) > hyst)) )
  {
    return new;
  }
  else
  {
    return old;
  }
}

void
send_byte(uint8_t bts)
{
  uint8_t parity=0;

  PORTB&=~_BV(PIN_POT1);
  DDRB|=_BV(PIN_POT1); // set output

  for(uint8_t k=8; k; k--)
  {
    _delay_us(SBYTE_LDLY_US);
    PORTB|=_BV(PIN_POT1);
    _delay_us(SBYTE_HDLY_US);
    PORTB&=~_BV(PIN_POT1);

    if(bts&0x01)
    {
      _delay_us(SBYTE_XDLY_US);
      parity^=1;
    }

    bts>>=1;
  }

  _delay_us(SBYTE_LDLY_US);
  PORTB|=_BV(PIN_POT1);
  _delay_us(SBYTE_HDLY_US);
  PORTB&=~_BV(PIN_POT1);
  _delay_us(SBYTE_LDLY_US);

  if(parity)
  {
    _delay_us(SBYTE_XDLY_US);
  }

  PORTB|=_BV(PIN_POT1);
  _delay_us(SBYTE_HDLY_US);
  PORTB&=~_BV(PIN_POT1);
  _delay_us(SBYTE_LDLY_US/2);

  DDRB&=~_BV(PIN_POT1); // set input
}
