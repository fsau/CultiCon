void
set_params(uint8_t mode, uint8_t power)
{
  uint8_t new_deltaON, new_deltaOFF = 220;
  uint16_t new_con;
  enum trig_mode new_tmode;

#if defined(SPOT3000)
  switch(mode) // 3000
  {
    default:
    case 0: // carvão (d)
      new_con = 120*5;
      new_deltaON = 128-5*power;
      new_tmode = t_manual;
      break;
    case 1: // cobre (c)
      new_con = 120*3;
      new_deltaON = 128-5*power;
      new_tmode = t_manual;
      break;
    case 2: // arruela (b)
      new_con = 85;
      new_deltaON = 150-8*power;
      new_tmode = t_pulse;
      break;
    case 3: // estrela (a)
      new_con = 18;
      new_deltaON = 150-8*power;
      new_tmode = t_pulse;
      break;
  }
#elif defined(SPOT2000A)
  switch(mode) // 2000a
  {
    default:
    case 0:
    case 1: // arruela (manual)
      new_con = 120*15;
      new_deltaON = 150-8*power;
      new_tmode = t_manual;
      break;
    case 2:
    case 3: // estrela
      new_con = 20;
      new_deltaON = 150-8*power;
      new_tmode = t_pulse;
      break;
  }
#elif defined(SPOT865)
  switch(mode) // 865
  {
    default:
    case 0:
    case 1: // estrela
      new_con = 20;
      new_deltaON = 150-8*power;
      new_tmode = t_pulse;
      break;
    case 2:
    case 3: // arruela (manual)
      new_con = 120*15;
      new_deltaON = 150-8*power;
      new_tmode = t_manual;
      break;
  }
#elif defined(SPOT840)
  new_con = 6+5*mode;
  new_deltaON = 150-8*power;
  new_tmode = t_pulse;
#endif

  g_con = new_con;
  g_tmode = new_tmode;

  load_onoff_tasks(new_deltaON, new_deltaOFF);
}

void
update_tstate(void)
{
  // update counters & output:
  if(g_tstate&TSTB_OHIGH)
  {
    if(g_tstate&TSTB_TMANU)
    {
      if(~g_tstate&TSTB_TRIGD)
      {
#ifndef TEMP_SW_POWER
        g_tcnt_cdown += g_con-g_tcnt_part; // elapsed time
#endif
        g_tcnt_part=0;
      }
    }

    if(g_tcnt_part==0)
    {
      g_tstate&=TSTB_TRIGD; // clear everything but trigger bit
      g_tcnt_cdown += WAIT_COUNTDOWN;

      if(FLAG_IS_CLEAR(FLAG_PHASE))
      {
        CLEAR_FLAG(FLAG_LPHAS);
        eeprom_update_byte(&e_last_phase,0);
      }
      else
      {
        SET_FLAG(FLAG_LPHAS);
        eeprom_update_byte(&e_last_phase,1);
      }
    }
    else
    {
      g_tcnt_part--;
    }
  }
  else
  {
    OUTPUT_OFF();
  }

  // check trigger:
  if(FLAG_IS_SET(FLAG_TRIGR))
  {
    if( !(g_tstate&(TSTB_TRIGD|TSTB_OHIGH)) && (g_tcnt_cdown==0)
    && (!FLAG_IS_SET(FLAG_LPHAS) == !FLAG_IS_CLEAR(FLAG_PHASE))
    && FLAG_IS_SET(FLAG_ENABL))
    {
      g_tstate=TSTB_TRIGD|TSTB_OHIGH;
      g_tcnt_part = g_con;

      set_params(g_cmode,0); // first cycle low power

      if(g_tmode==t_manual)
      {
        g_tstate|=TSTB_TMANU;
      }
      else
      {
        g_tstate&=~TSTB_TMANU;
      }

      if(g_tmode!=t_cont)
      {
        g_tstate|=TSTB_PULSE;
      }
      else
      {
        g_tstate&=~TSTB_PULSE;
      }
    }
  }
  else
  {
    g_tstate&=~TSTB_TRIGD;
  }

  if(g_tcnt_cdown>0) g_tcnt_cdown--;
}

void
out_on_update(void)
{
  set_params(g_cmode, g_cpower);
  if((g_tstate&TSTB_OHIGH)&&(g_tmode != t_off)&&FLAG_IS_SET(FLAG_ENABL))
  {
    OUTPUT_ON();
  }
}

void
out_off_update(void)
{
  if((g_tstate&TSTB_PULSE)||(~g_tstate&TSTB_OHIGH))
  {
    OUTPUT_OFF();
  }
  update_tstate();
  TOGGLE_FLAG(FLAG_PHASE);
}
