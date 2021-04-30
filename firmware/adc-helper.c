uint16_t
adc_get(uint8_t admux_chan)
{
  ADMUX = ADMUX_DEFAULT|admux_chan;
  ADCSRA |= _BV(ADSC); // start conversion
  loop_until_bit_is_set(ADCSRA, ADIF); // wait until complete
  ADCSRA |= _BV(ADIF); // clear adc interrupt flag
  return ADC;
}
