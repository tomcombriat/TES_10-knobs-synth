/*
   Combriat 2020

  XORAND Sax mk3
  A 10k synth flavor to be used with an EWI. Supports polyphony (for chords) and breath control over volume or/and filter.


  Use the TES-branch of tomcombriat/Mozzi for MetaOsc.


  Mozzi config should be set to use an external audio
  Compilation should be -O3, OC @ 128MHz.

  TODO: battery check.
*/



#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h>
#include<MetaOscil.h>
#include<SPI.h>


#include <mozzi_midi.h>
#include <mozzi_fixmath.h>
#include <Smooth.h>
#include <ADSR.h>
#include <LowPassFilter.h>
#include <AudioDelayFeedback.h>
#include <Portamento.h>
#include "midi_handles.h"
#include "oscil_declaration.h"
#include <tables/cos2048_int8.h>


#define CONTROL_RATE 2048 // Hz, powers of 2 are most reliable
//#define CONTROL_RATE 4096 // Hz, powers of 2 are most reliable

#define LED PA8

#define POLYPHONY 8


Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCarrier[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aMod[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);


ADSR <AUDIO_RATE, AUDIO_RATE, unsigned long> envelope[POLYPHONY];

//LowPassFilter16 lpf;
//LowPassFilter lpf;
//Smooth <unsigned int> cutoff_smooth(0.995f);  // 0.999 -> 15ms  // a bit sluggish?
// 0.995 -> 7ms
Smooth <int> breath_smooth(0.98f);  // if updated at AUDIO_RATE:
// 0.99 -> 15ms maximal raise time
// 0.98 -> 8ms
// 0.9999 -> 1.3s (!!!!)
//Portamento<CONTROL_RATE> porta;

byte notes[POLYPHONY] = {0};

int  pitchbend = 0, pitchbend_amp = 2, resonance = 0, breath_sens = 0, volume = 0;
byte oscil_state[POLYPHONY], oscil_rank[POLYPHONY], runner = 0, prev_MSB_volume = 0;
bool sustain = false;
bool osc_is_on[POLYPHONY] = {false};
unsigned int chord_attack = 1, chord_release = 1, cutoff = 0, prev_cutoff = 0, midi_cutoff = 0;
int toggle = 0;



Q16n16 carrier_freq[POLYPHONY];
Q16n16 mod_freq[POLYPHONY];

Q8n8 mod_index;
Q16n16 deviation[POLYPHONY];
Q8n8 mod_to_carrier_ratio;

Q8n8 mod_index_rm;
Q16n16 deviation_rm[POLYPHONY];



// External audio output parameters and DAC declaration
SPIClass mySPI(2);
#define WS_pin PB8




MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);



void set_freq(byte i, bool reset_phase = false)
{

  osc_is_on[i] = true;
  Q16n16 freq = Q16n16_mtof(Q8n0_to_Q16n16(notes[i]) + (pitchbend << 3) * pitchbend_amp);
  freq = freq >> 1; // For stable FM, next need to be called, leading to twice the freq as a result

  carrier_freq[i] = freq;
  mod_freq[i] = ((freq >> 8) * mod_to_carrier_ratio);
  deviation[i] = ((mod_freq[i] >> 16) * mod_index);
  deviation_rm[i] = ((freq >> 16) * mod_index_rm);
  aMod[i].setFreq_Q16n16(mod_freq[i]);
  aCarrier[i].setFreq_Q16n16(freq);



}


int three_values_knob(int val, int i)
{
  switch (i)
  {
    case 0:
      {
        if (val > 512) {
          return 0;
        }
        else return (512 - val);
      }
    case 1:
      {
        if (val < 512) return val;
        else return 1024 - val;
      }
    case 2:
      {
        if (val < 512 ) return 0;
        else return val - 512;
      }
  }
}




void setup() {
  //Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  mySPI.begin();
  delay(100);
  mySPI.beginTransaction(SPISettings(2000000000, MSBFIRST, SPI_MODE0)); //MSB first, according to the DAC spec

  pinMode(WS_pin, OUTPUT);

  pinMode(PB1, INPUT_ANALOG);
  pinMode(PB0, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PA2, INPUT);
  pinMode(PA3, INPUT);
  pinMode(PA4, INPUT);
  pinMode(PA5, INPUT);
  pinMode(PA6, INPUT);
  pinMode(PA7, INPUT);


  for (byte i = 0; i < POLYPHONY; i++)
  {

    envelope[i].setADLevels(128, 128);
    envelope[i].setTimes(1, 1, 6500000, 10);
  }


  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandlePitchBend(HandlePitchBend);
  //  MIDI.setHandleAfterTouchChannel(HandleAfterTouchChannel);




  MIDI.begin(MIDI_CHANNEL_OMNI);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);

  MIDI.turnThruOff (); // hardwired
  startMozzi(CONTROL_RATE);
  digitalWrite(LED, LOW);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);


}







void loop() {
  audioHook();
}




void audioOutput(const AudioOutput f) // f is a structure containing both channels
{
  //Serial.println(f.l()>>8);
  // analogWrite(LED, f.l()>>8);
  digitalWrite(WS_pin, LOW);  //select Right channel
  mySPI.transfer16(f.l());


  digitalWrite(WS_pin, HIGH);  // select Left channel
  //  mySPI.transfer16(f.l());
  //digitalWrite(LED, HIGH);
}




void updateControl() {
  while (MIDI.read());

  toggle++;

  switch (toggle)
  {
    case 1:
      mod_to_carrier_ratio = mozziAnalogRead(PA6) >> 2 ;
      break;
    case 2:
      mod_index = mozziAnalogRead(PB0) << 2 ;
      break;
    case 3:
      mod_index_rm = mozziAnalogRead(PA5) ;
      break;
    case 4:

      break;
    case 5:
      chord_release = mozziAnalogRead(PA7) >> 0 ;
      break;
    case 6:
      chord_attack = mozziAnalogRead(PB1) >> 0 ;
      break;
    case 7:

      break;
    case 8:

      break;

    case 9:
      breath_sens = mozziAnalogRead(PA1) >> 4;
      toggle = 0;
      break;
  }

  for (byte i = 0; i < POLYPHONY; i++)
  {
    mod_freq[i] = ((carrier_freq[i] >> 8) * mod_to_carrier_ratio);
    deviation[i] = ((mod_freq[i] >> 16) * mod_index);
    deviation_rm[i] = ((carrier_freq[i] >> 16) * mod_index_rm);
    aMod[i].setFreq_Q16n16(mod_freq[i]);
  }
}

AudioOutput_t updateAudio() {

  int sample = 0;

  int breath_next = breath_smooth.next((volume * breath_sens - ((breath_sens - 255) << 14)) >> 11);
  //if (breath_next == 0)
  if ((volume >> 7) == 0)
  {
    for (byte i = 0; i < POLYPHONY; i++)
    {
      envelope[i].noteOff();
      osc_is_on[i] = false; // so that chord do not fade out during next note afer a short pause
      oscil_state[i] = 0;   // everybody reset
    }
  }


  for (byte i = 0; i < POLYPHONY; i++)
  {

    envelope[i].update();
    int env_next = envelope[i].next();  // for enveloppe to roll even if it is not playing
    if (envelope[i].playing() && osc_is_on[i])
    {
      long partial_sample = 0;

      Q15n16 modulation_rm = deviation_rm[i] * aCarrier[i].next() >> 8 ;
      Q15n16 modulation = deviation[i] * aMod[i].phMod(modulation_rm) >> 8 ;
      partial_sample = aCarrier[i].phMod(modulation);


      //sample += (partial_sample * env_next) >> 1;
      sample += partial_sample;

    }
  }

  //sample = (sample * breath_next) >> 5 ;






  return MonoOutput::from16Bit(sample << 6).clip();

}
