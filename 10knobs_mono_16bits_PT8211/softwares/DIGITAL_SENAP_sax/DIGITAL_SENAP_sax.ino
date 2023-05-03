/*
   Combriat 2022-2023

  Digital Senap Sax mk1
  A 10k synth flavor to be used with an EWI. Supports polyphony (for chords) and breath control over volume or/and filter.



  Mozzi config should be set to use an external audio
  Compilation should be -O3, OC @ 128MHz.

  TODO: battery check.
*/


//#define RINGING_CHORDS // chords do not follow breath when in the decaying phase if the breath is higher than their noteOff velocity
#define DITHERING  // dithering before shifting down to 16 bits
#define LEGACYSTM  // this code is normally compiled with the "original" STM32duino. Uncomment this line to use the ST supported core.
#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h>
#include <MetaOscil.h>
#include <SPI.h>

#include <mozzi_rand.h>
#include <mozzi_midi.h>
#include <mozzi_fixmath.h>
#include <Smooth.h>
#include <ADSR.h>
#include <ResonantFilter.h>
#include <AudioDelayFeedback.h>
#include <Portamento.h>
#include "midi_handles.h"
#include "oscil_declaration.h"
#include "dual_type_pot.h"
#include "computeMaxDeviation.h"
#include <tables/cos2048_int8.h>


#define CONTROL_RATE 4096  // Hz, powers of 2 are most reliable
//#define CONTROL_RATE 2048


#define LED PA8

//#define POLYPHONY 12
#define POLYPHONY 10


Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCarrier[POLYPHONY] = { Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                             Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                             Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                             Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                             Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA) };

Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aMod[POLYPHONY] = { Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                         Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                         Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                         Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA),
                                                         Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA), Oscil<COS2048_NUM_CELLS, AUDIO_RATE>(COS2048_DATA) };


ADSR<AUDIO_RATE, AUDIO_RATE, unsigned long> envelope[POLYPHONY];

LowPassFilter16 lpf;
Smooth<unsigned int> cutoff_smooth(0.995f);  // 0.999 -> 15ms  // a bit sluggish?// 0.995 -> 7ms
Smooth<unsigned int> rm_smooth(0.995f);      // 0.999 -> 15ms  // a bit sluggish?// 0.995 -> 7ms
Smooth<int> breath_smooth(0.98f);            // if updated at AUDIO_RATE:
// 0.99 -> 15ms maximal raise time
// 0.98 -> 8ms
// 0.9999 -> 1.3s (!!!!)

Smooth<Q16n16> deviation_smooth[POLYPHONY] = { Smooth<Q16n16>(0.001f) };

byte notes[POLYPHONY] = { 100 };

int pitchbend = 0, pitchbend_amp = 2, resonance = 0, breath_sens = 0, volume = 0, breath_on_cutoff = 0, breath_on_rm = 0, prev_resonance = 0, toggle = 0;
byte oscil_state[POLYPHONY], oscil_rank[POLYPHONY], runner = 0, prev_MSB_volume = 0;
bool sustain = false;
bool osc_is_on[POLYPHONY] = { false };
int breath_at_note_off[POLYPHONY] = { 0 }, breath_next = 0;
unsigned int chord_attack = 1, chord_release = 1, cutoff = 0, prev_cutoff = 0, midi_cutoff = 0;
uint32_t deviation_rm;
byte breath_on_vol_LUT[256];




Q16n16 maxDeviation[8][128];

Q16n16 carrier_freq[POLYPHONY];
Q24n8 mod_freq[POLYPHONY];


Q16n16 deviation_pot;
Q16n16 deviation[POLYPHONY], deviation_sm[POLYPHONY];
Q8n8 mod_to_carrier_ratio, mod_to_carrier_ratio_old;


Q16n16 deviation_rm_pot;



// External audio output parameters and DAC declaration
#ifdef LEGACYSTM
SPIClass mySPI(2);
#else
SPIClass mySPI(PB15, PB14, PB13);
#endif
#define WS_pin PB8


#ifndef LEGACYSTM
HardwareSerial Serial3(PB11, PB10);
#endif
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);


void set_freq(byte i, bool reset_phase = false) {
  osc_is_on[i] = true;
  Q16n16 current_note = Q8n0_to_Q16n16(notes[i]) + (pitchbend << 3) * pitchbend_amp;  // maybe put the shift here instead ?
  Q16n16 freq = Q16n16_mtof(current_note);
  freq = freq >> 1;  // For stable FM, next need to be called, leading to twice the freq as a result

  carrier_freq[i] = freq;

  compute_fm_param(i, reset_phase);
}

inline void compute_fm_param(byte i, bool reset_phase) {
  /*  mod_freq[i] = ((carrier_freq[i] >> 8) * mod_to_carrier_ratio);

    aMod[i].setFreq_Q16n16(mod_freq[i]);*/

  mod_freq[i] = ((carrier_freq[i] >> 8) * mod_to_carrier_ratio) >> 8;
  /*  Serial.print(Q16n16_to_float(carrier_freq[i]));
    Serial.print(" ");
    Serial.print(Q24n8_to_float(mod_freq[i]));
    Serial.print(" ");
    Serial.println(Q16n16_to_float(mod_freq[i]));*/
  // put the aCarrier set freq here ? With noInterrupts around?

  aCarrier[i].setFreq_Q16n16(carrier_freq[i]);
  aMod[i].setFreq_Q24n8(mod_freq[i]);
  //aMod[i].setPhaseFractional(aCarrier[i].getPhaseFractional());
  if (reset_phase) {
    aCarrier[i].setPhase(0);
    aMod[i].setPhase(0);
  }

  /*
    Serial.print(i);
    Serial.print(" ");
    Serial.print(aCarrier[i].getPhaseFractional());
    Serial.print(" ");
    Serial.println(aMod[i].getPhaseFractional());*/
}











int three_values_knob(int val, int i) {
  switch (i) {
    case 0:
      {
        if (val > 512) {
          return 0;
        } else return (512 - val);
      }
    case 1:
      {
        if (val < 512) return val;
        else return 1024 - val;
      }
    case 2:
      {
        if (val < 512) return 0;
        else return val - 512;
      }
  }
}




void setup() {
  pinMode(LED, OUTPUT);
  mySPI.begin();
  delay(100);
  mySPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));  //MSB first, according to the DAC spec

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

  for (int i = 0; i < 256; i++) {
    if (i != 0) breath_on_vol_LUT[i] = log((float)i) / log(255.) * 255;
    else breath_on_vol_LUT[i] = 0;
  }

  for (byte i = 0; i < POLYPHONY; i++) {
    envelope[i].setADLevels(128, 128);
    envelope[i].setTimes(1, 1, 6500000, 10);
  }

  computeMaxDeviation(maxDeviation[0], 0.0654, 680., 128);
  computeMaxDeviation(maxDeviation[1], 0.0654, 258., 128);
  computeMaxDeviation(maxDeviation[2], 0.0654, 256., 128);
  computeMaxDeviation(maxDeviation[3], 0.0654, 200., 128);
  computeMaxDeviation(maxDeviation[4], 0.0654, 200., 128);
  computeMaxDeviation(maxDeviation[5], 0.0654, 200., 128);
  computeMaxDeviation(maxDeviation[6], 0.0654, 200., 128);
  computeMaxDeviation(maxDeviation[7], 0.0654, 200., 128);




  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandlePitchBend(HandlePitchBend);
  //  MIDI.setHandleAfterTouchChannel(HandleAfterTouchChannel);


  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();  // hardwired
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);

  startMozzi(CONTROL_RATE);
  digitalWrite(LED, LOW);
}







void loop() {
  audioHook();
}




void audioOutput(const AudioOutput f)  // f is a structure containing both channels
{
  digitalWrite(WS_pin, LOW);  //select Right channel
  mySPI.transfer16(f.l());
  digitalWrite(WS_pin, HIGH);  // select Left channel
}




void updateControl() {
  while (MIDI.read())
    ;

  if ((volume) == 0) {
    for (byte i = 0; i < POLYPHONY; i++) {
      envelope[i].noteOff();
      osc_is_on[i] = false;  // so that chord do not fade out during next note afer a short pause
      oscil_state[i] = 0;    // everybody reset
      volume = 0;
    }
  }


  toggle++;

  switch (toggle) {
    case 1:
      //mod_to_carrier_ratio = mozziAnalogRead(PA6) >> 2;  //10bits: 2integers, 8 fractionnal (up to 4)
      mod_to_carrier_ratio = dual_type_pot(mozziAnalogRead(PA6));
      if (mod_to_carrier_ratio != mod_to_carrier_ratio_old) {
        mod_to_carrier_ratio_old = mod_to_carrier_ratio;
        for (byte i = 0; i < POLYPHONY; i++) compute_fm_param(i, false);
      }
      break;
    case 2:
      deviation_pot = mozziAnalogRead(PB0) << 10;
      for (byte i = 0; i < POLYPHONY; i++) {
        if (osc_is_on[i]) deviation[i] = min(maxDeviation[Q8n8_to_Q8n0(mod_to_carrier_ratio)][Q16n16_to_Q16n0(Q8n0_to_Q16n16(notes[i]) + (pitchbend << 3) * pitchbend_amp)], deviation_pot);
      }
      break;
    case 3:
      deviation_rm_pot = mozziAnalogRead(PA5) << 4;
      //for (byte i = 0; i < POLYPHONY; i++)  compute_fm_param(i);
      break;
    case 4:
      breath_on_rm = (mozziAnalogRead(PA3) >> 4);
      break;
    case 5:
      chord_release = mozziAnalogRead(PA7) >> 0;
      break;
    case 6:
      chord_attack = mozziAnalogRead(PB1) >> 0;
      break;
    case 7:
      breath_on_cutoff = (mozziAnalogRead(PA4) >> 4);
      break;
    case 8:
      resonance = mozziAnalogRead(PA2);
      break;
    case 9:
      breath_sens = mozziAnalogRead(PA1) >> 4;
      toggle = 0;
      break;
  }

  //for (byte i = 0; i < POLYPHONY; i++) deviation_sm[i] = deviation_smooth[i].next(deviation[i]);/
  for (byte i = 0; i < POLYPHONY; i++) deviation_sm[i] = deviation[i];
  /*
    Serial.print(volume);
    Serial.print(" ");
    unsigned int tamp = volume * (287-breath_sens);
    tamp = tamp >> 5;
    if (tamp > 16384) tamp = 16384;
    Serial.println(tamp);*/
}

int countt = 0;

AudioOutput_t updateAudio() {
  long sample = 0;
  cutoff = cutoff_smooth.next(((breath_on_cutoff * volume) >> 6) + (midi_cutoff << 9));  // >>8
  if (cutoff > 65535) cutoff = 65535;
  if (cutoff != prev_cutoff || resonance != prev_resonance) {
    lpf.setCutoffFreqAndResonance(cutoff, resonance << 4);
    prev_cutoff = cutoff;
    prev_resonance = resonance;
  }
  //breath_next = breath_smooth.next((volume * breath_sens - ((breath_sens - 255) << 14)) >> 11);  //11bits
  //unsigned int tamp_volume = volume * (287-breath_sens);  //14+5 = 19bits
  unsigned int tamp_volume = (volume * (263 - breath_on_vol_LUT[breath_sens]));
  tamp_volume = tamp_volume >> 1;
  if (tamp_volume > 65535) tamp_volume = 65535;  //16 bits
  breath_next = breath_smooth.next(tamp_volume);
  //deviation_rm = rm_smooth.next(((breath_on_rm * volume)>>6) + deviation_rm_pot);
  deviation_rm = rm_smooth.next(((breath_on_rm * volume) >> 6) + deviation_rm_pot << 2);
  //if (deviation_rm > 524288) deviation_rm = 524288;

  /*
    if ((volume >> 7) == 0) //reduce
    {
    for (byte i = 0; i < POLYPHONY; i++)
    {
      envelope[i].noteOff();
      osc_is_on[i] = false; // so that chord do not fade out during next note afer a short pause
      oscil_state[i] = 0;   // everybody reset
      volume = 0;
    }
    }
  */

  for (byte i = 0; i < POLYPHONY; i++) {
    envelope[i].update();
    int env_next = envelope[i].next();  // for enveloppe to roll even if it is not playing
    // if (!envelope[i].playing() && osc_is_on[i]) osc_is_on[i] = false;
    if (envelope[i].playing() && osc_is_on[i]) {
      long partial_sample = 0;
      Q15n16 modulation_rm = deviation_rm * aCarrier[i].next() >> 8;
      Q15n16 modulation = deviation_sm[i] * aMod[i].phMod(modulation_rm) >> 8;
      partial_sample = aCarrier[i].phMod(modulation);  // 8bits


#ifdef RINGING_CHORDS
      if (breath_at_note_off[i] != 0 && breath_at_note_off[i] < breath_next) partial_sample *= breath_at_note_off[i];

      else partial_sample *= breath_next;
#endif
      sample += (partial_sample * env_next);  // 15bits
    }
  }
#ifndef RINGING_CHORDS
  sample = (sample * breath_next);  //  //31
#endif
#ifdef DITHERING
  sample += rand(-16384, 16384);  //
#endif
  sample = lpf.next(sample >> 15);  // that's 16bits, overflowing with chords?



  return MonoOutput::fromNBit(16, sample).clip();
}
