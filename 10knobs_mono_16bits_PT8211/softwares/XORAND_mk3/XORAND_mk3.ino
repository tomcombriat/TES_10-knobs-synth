/*
   Combriat 2020

  XORAND mk3
  A 10k synth flavor to be used with an keyboard


  Use the TES-branch of tomcombriat/Mozzi for MetaOsc.


  Mozzi config should be set to use an external audio
  Compilation should be -O3, OC @ 128MHz.

  TODO: battery check.
*/


//#define DITHERING   // dithering before shifting down to 16 bits
#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h>
#include<MetaOscil.h>
#include<SPI.h>

#include <mozzi_rand.h>
#include <mozzi_midi.h>
#include <mozzi_fixmath.h>
#include <Smooth.h>
#include <ADSR.h>
#include <LowPassFilter.h>
#include <AudioDelayFeedback.h>
#include <Portamento.h>
#include "midi_handles.h"
#include "oscil_declaration.h"


#define CONTROL_RATE 1024 // Hz, powers of 2 are most reliable
//#define CONTROL_RATE 4096 // Hz, powers of 2 are most reliable

#define LED PA8


Oscil<COS512_NUM_CELLS, AUDIO_RATE> aSin[POLYPHONY] = Oscil<COS512_NUM_CELLS, AUDIO_RATE> (COS512_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aMod[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);
//Oscil<COS2048_NUM_CELLS, AUDIO_RATE> LFO[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);


ADSR <AUDIO_RATE, AUDIO_RATE, unsigned long> envelope[POLYPHONY];

LowPassFilter16 lpf;


byte notes[POLYPHONY] = {0};
int wet_dry_mix;
int mix1;
int mix2;
int mix_oscil, pitchbend = 0, pitchbend_amp = 2, aftertouch = 0, resonance = 0, prev_resonance = 0;
byte oscil_state[POLYPHONY], oscil_rank[POLYPHONY], runner = 0;
bool sustain = false;
bool osc_is_on[POLYPHONY] = {false};
//unsigned int chord_attack = 1, chord_release = 1,cutoff = 0,prev_cutoff = 0,midi_cutoff = 0;
unsigned int attack = 1, release = 1, cutoff = 0, prev_cutoff = 0, midi_cutoff = 0, filter_attack = 1, filter_release = 1;
int toggle = 0;

Q16n16 deviation = 0;
Q8n8 mod_to_carrier_ratio = 0;
Q24n8 mod_freq[POLYPHONY];
Q16n16 carrier_freq[POLYPHONY];





// External audio output parameters and DAC declaration
SPIClass mySPI(2);
#define WS_pin PB8




MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);



void set_freq(byte i, bool reset_phase = false)
{

  osc_is_on[i] = true;
  Q16n16 freq = Q16n16_mtof(Q8n0_to_Q16n16(notes[i]) + (pitchbend << 3) * pitchbend_amp);
carrier_freq[i] = freq;
  aSin[i].setFreq_Q16n16(freq);
  aSquare[i].setFreq_Q16n16(freq);
  aTri[i].setFreq_Q16n16(freq);
  aSaw[i].setFreq_Q16n16(freq);

  //mod_freq[i] = ((freq >> 8) * mod_to_carrier_ratio) >> 8;
 compute_FM(i);

}

void compute_FM(byte i)
{
   aMod[i].setFreq_Q24n8(((carrier_freq[i] >> 8) * mod_to_carrier_ratio) >> 8);
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
  Serial.begin(115200);
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

    aSquare[i].setOscils(&aSq75[i], &aSq81[i], &aSq88[i], &aSq96[i], &aSq106[i], &aSq118[i], &aSq134[i], &aSq154[i], &aSq182[i], &aSq221[i], &aSq282[i], &aSq356[i], &aSq431[i], &aSq546[i], &aSq630[i], &aSq744[i], &aSq910[i], &aSq1170[i], &aSq1638[i], &aSq2730[i], &aSq8192[i]);
    aSquare[i].setCutoffFreqs(75 * 2, 81 * 2, 88 * 2, 96 * 2, 106 * 2, 118 * 2, 134 * 2, 154 * 2, 182 * 2, 221 * 2, 282 * 2, 356 * 2, 431 * 2, 546 * 2, 630 * 2, 744 * 2, 910 * 2, 1170 * 2, 1638 * 2, 2730 * 2, 8192 * 2);

    aSaw[i].setOscils(&aSaw154[i], &aSaw182[i], &aSaw221[i], &aSaw282[i], &aSaw356[i], &aSaw431[i], &aSaw546[i], &aSaw630[i], &aSaw744[i], &aSaw910[i], &aSaw1170[i], &aSaw1638[i], &aSaw2730[i], &aSaw8192[i]);
    aSaw[i].setCutoffFreqs( 154 * 2, 182 * 2, 221 * 2, 282 * 2, 356 * 2, 431 * 2, 546 * 2, 630 * 2, 744 * 2, 910 * 2, 1170 * 2, 1638 * 2, 2730 * 2, 8192 * 2);
    aTri[i].setOscils(&aTri106[i], &aTri118[i], &aTri134[i], &aTri154[i], &aTri182[i], &aTri221[i], &aTri282[i], &aTri356[i], &aTri431[i], &aTri546[i], &aTri630[i], &aTri744[i], &aTri910[i], &aTri1170[i], &aTri1638[i], &aTri2730[i], &aTri8192[i]);
    aTri[i].setCutoffFreqs( 106 * 2, 118 * 2, 134 * 2, 154 * 2, 182 * 2, 221 * 2, 282 * 2, 356 * 2, 431 * 2, 546 * 2, 630 * 2, 744 * 2, 910 * 2, 1170 * 2, 1638 * 2, 2730 * 2, 8192 * 2);
    aSaw[i].setPhase(512 >> 2 );
    aSin[i].setPhase(512 >> 2 );  // test

  }


  // lpf.setResonance(25);



  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandlePitchBend(HandlePitchBend);
  MIDI.setHandleAfterTouchChannel(HandleAfterTouchChannel);

  //Serial.begin(115200);


  MIDI.begin(2);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);

  MIDI.turnThruOff (); //for speed
  startMozzi(CONTROL_RATE);
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
      mix1 =  mozziAnalogRead(PB0) >> 4;  // very steppy, but not mix2, WHY????
      break;
    case 2:
      mix2 =  mozziAnalogRead(PA6) >> 4;
      break;
    case 3:
      wet_dry_mix = mozziAnalogRead(PA3) >> 2;  // goos to 1024
      break;
    case 4:
      mix_oscil = mozziAnalogRead(PA5) >> 4 ;
      break;
    case 5:
      release = mozziAnalogRead(PA7) ;
      for (byte i = 0; i < POLYPHONY; i++) envelope[i].setReleaseTime(release);
      break;
    case 6:
      attack = mozziAnalogRead(PB1);
      for (byte i = 0; i < POLYPHONY; i++) envelope[i].setAttackTime(attack);
      break;
    case 7:
      cutoff  = mozziAnalogRead(PA4) << 4;
      resonance  = mozziAnalogRead(PA2) << 4;
      lpf.setCutoffFreqAndResonance(cutoff, resonance);
      break;
    case 8:
      deviation = mozziAnalogRead(PA1);
      
      toggle = 0;
      break;
  }
}

AudioOutput_t updateAudio() {

  long sample = 0;

  for (byte i = 0; i < POLYPHONY; i++)
  {
    envelope[i].update();
    int env_next = envelope[i].next();  // for enveloppe to roll even if it is not playing
    if (envelope[i].playing())
    {
      long partial_sample = 0;

      int aSin_next;
      int aSquare_next;
      int aTri_next;
      int aSaw_next;


      /*
            aSin_next = aSin[i].next();
            aSquare_next = aSquare[i].next();
            aTri_next = aTri[i].next();
            aSaw_next = aSaw[i].next();
      */

      aSin_next = aSin[i].phMod(deviation * aMod[i].next());
      aSquare_next = aSquare[i].phMod(deviation * aMod[i].next());
      aTri_next = aTri[i].phMod(deviation * aMod[i].next());
      aSaw_next = aSaw[i].phMod(deviation * aMod[i].next());

      int oscil1 = (((aSin_next * (255 - mix1) + aSquare_next * (mix1)) >> 8 ) * (255 - mix_oscil)); // >> 5 ;// 17 bits
      int oscil2 = (((aTri_next * (255 - mix2) + aSaw_next * (mix2)) >> 8 ) * mix_oscil);// >> 5;

      int dry = oscil1 + oscil2; //18
      int wet1 = (oscil1 xor oscil2);
      int wet2 = oscil1 & oscil2;

      partial_sample += ((three_values_knob(wet_dry_mix, 0) >> 1) * wet1)  ;
      partial_sample += ((three_values_knob(wet_dry_mix, 1) >> 1) * dry)  ;
      partial_sample += ((three_values_knob(wet_dry_mix, 2) >> 1) * wet2) ; //  26

      //Serial.println(partial_sample);
      //partial_sample = lpf[i].next(partial_sample >> 10); //16bits
      partial_sample = partial_sample >> 10;
      sample += (partial_sample * env_next);  //23

    }
  }

  sample = lpf.next(sample);

#ifdef DITHERING
  sample += rand(-128, 128);
#endif




  return MonoOutput::fromNBit(23, sample).clip();

}
