ISR(TIM0_COMPA_vect) // run task interrupt
{
  uint8_t old_ocr0a = get_curr_cmp(), new_ocr0a;

  do
  {
    uint8_t func_run = get_curr_func();
    load_next_task();
    new_ocr0a = get_curr_cmp();

    switch(func_run)
    {
      case 1:
      out_off_update();
      break;
      case 2:
      out_on_update();
      break;
      default:
      break;
    }
  } while (new_ocr0a == old_ocr0a);

  OCR0A = new_ocr0a;
}

ISR(TIM0_COMPB_vect) // missing/self sync generator
{
  uint8_t timer0_val = TCNT0-PER_MAX_DELTA/2;
  if(ext_sync(timer0_val))
  {
    CLEAR_FLAG(FLAG_LOOP);
    OCR0B += g_mean_per;
  }

#ifndef SELF_SYNC_DEBUG
  g_sync_fail++;
  if(g_sync_fail>=PER_MAX_DELTA)
  {
    while(1)
    {
      OUTPUT_OFF();
      _NOP();
    }
  }
#endif
}

ISR(INT0_vect)
{
  uint8_t timer0_val = TCNT0;
  if(ext_sync(timer0_val))
  {
    CLEAR_FLAG(FLAG_LOOP);
    // OCR0A = get_curr_cmp();
    OCR0B = timer0_val + g_mean_per + PER_MAX_DELTA/2; // missing sync gen
    g_sync_fail=0;
  }
}
