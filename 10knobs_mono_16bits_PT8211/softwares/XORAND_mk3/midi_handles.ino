#include "midi_handles.h"
#include "oscil_declaration.h"



/*********************
       NOTE ON
 ********************/
void HandleNoteOn(byte channel, byte note, byte velocity)
{

  byte min_rank = 255;
  int empty_arg = -1;
  for (byte i = 0; i < POLYPHONY; i++)
  {
    if (notes[i] == note)
    {
      empty_arg = i;
      break;
    }
  }
  if (empty_arg == -1)
  {
    for (byte i = 0; i < POLYPHONY; i++)  //take a non playing oscil
    {
      if (!envelope[i].playing() && oscil_rank[i] < min_rank)
      {
        empty_arg = i;
        min_rank = oscil_rank[i];
      }
    }
  }
  if (empty_arg == -1)  //kill a oscil in release phase
  {
    min_rank = 255;
    for (byte i = 0; i < POLYPHONY; i++)
    {
      if (oscil_state[i] == 0 && oscil_rank[i] < min_rank)
      {
        empty_arg = i;
        min_rank = oscil_rank[i];
      }
    }
  }


  if (empty_arg == -1)  // no empty oscil, kill one in sustain mode! (the oldest)
  {
    min_rank = 255;
    byte min_rank_arg = 0;
    for (byte i = 0; i < POLYPHONY; i++)
    {
      if (oscil_rank[i] < min_rank)
      {
        min_rank = oscil_rank[i];
        min_rank_arg  = i;
      }
    }
    empty_arg = min_rank_arg;
  }


  notes[empty_arg] = note;
  set_freq(empty_arg);

  //velocities[empty_arg]=velocity;
  envelope[empty_arg].setAttackLevel(velocity);
envelope[empty_arg].setDecayLevel(velocity);
  if (attack > 5 )    envelope[empty_arg].noteOn(true);

  else envelope[empty_arg].noteOn();




  oscil_state[empty_arg] = 1;




  byte max_rank = 0;
  for (byte i = 0; i < POLYPHONY; i++)
  {
    if (oscil_rank[i] > max_rank) max_rank = oscil_rank[i];
  }
  oscil_rank[empty_arg] = max_rank + 1;


  // shift all oscill
  min_rank = 255;
  for (byte i = 0; i < POLYPHONY; i++)
  {
    if (oscil_rank[i] < min_rank)
    {
      empty_arg = i;
      min_rank = oscil_rank[i];
    }
  }
  if (min_rank != 0) for (byte i = 0; i < POLYPHONY; i++) oscil_rank[i] -= min_rank;





}


/**********************
      NOTE OFF
 *********************/


void HandleNoteOff(byte channel, byte note, byte velocity)
{

  byte to_kill = 255;
  byte min_rank = 255;

  for (byte i = 0; i < POLYPHONY; i++)
  {
    if (note == notes[i] && oscil_state[i] == 1 && oscil_rank[i] < min_rank  )
    {
      min_rank = oscil_rank[i];
      to_kill = i;
    }
  }

  if (to_kill != 255)
  {
    if (!sustain)
    {
      envelope[to_kill].noteOff();
      oscil_state[to_kill] = 0;
    }
    else oscil_state[to_kill] = 2;

    //envelope[0].noteOff();
    for (byte i = 0; i < POLYPHONY; i++)
    {
      if (oscil_rank[i] > oscil_rank[to_kill]) oscil_rank[i] -= 1;
    }
  }
}




/*************************
  CONTROL CHANGE
************************/
void HandleControlChange(byte channel, byte control, byte val)
{
  switch (control)
  {
    case 64:    // sustain
      if (val == 0)
      {
        sustain = false;
        for (byte i = 0; i < POLYPHONY; i++)
        {
          if (oscil_state[i] == 2)
          {
            envelope[i].noteOff();
            oscil_state[i] = 0;
          }
        }
      }
      else sustain = true;
      break;

    /*
        case 1:  //modulation
          for (byte i = 0; i < POLYPHONY; i++) LFO[i].setFreq_Q16n16((Q16n16) (val << 13 ));
          if (val == 0 && mod) mod = false;
          else if (val != 0 && !mod) mod = true;
          break;*/
    /*
        case 74: //volume (MSB)
        //if (val > prev_MSB_volume || (val & 0b00000001111111) != 0) volume = (int) (val) << 7;
        if (val > prev_MSB_volume) volume = (int) (val) << 7;
        else volume = ((int) (val) << 7) + 0b00000001111111;
        prev_MSB_volume = val;
        break;

        case 75: //volume LSB
          volume &= 0b11111110000000;
          volume += val;

          break;*/

    case 1: //modulation
      //mod_to_carrier_ratio =((Q8n8) val);
      deviation = val << 2;

      //for (byte i = 0; i < POLYPHONY; i++) compute_FM(i);
      break;

    case 5: // pitchbend_amp
      pitchbend_amp = val;
      break;

  }
}



/**********************
      PITCHBEND
 *    ***************/
void HandlePitchBend(byte channel, int bend)
{
  pitchbend = bend;
  for (byte i = 0; i < POLYPHONY; i++)
  {
    if (envelope[i].playing() && osc_is_on[i]) set_freq(i, false);
  }
}

/*********************
   AFTERTOUCH
 * *******************/

void HandleAfterTouchChannel(byte channel, byte after)
{
  aftertouch = after;
}
