#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/cos2048_int8.h> // table for Oscils to play
#include<SPI.h>


Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aSin(COS2048_DATA);

SPIClass mySPI(2);
#define WS_pin PB8
#define LED PA8



void audioOutput(const AudioOutput f) // f is a structure containing both channels
{
  //Serial.println(f.l()>>8);
 //analogWrite(LED, f.l());
  digitalWrite(WS_pin, LOW);  //select Right channel
  mySPI.transfer16(f.l());


  digitalWrite(WS_pin, HIGH);  // select Left channel
    //mySPI.transfer16(f.l());
  //digitalWrite(LED, HIGH);
}
void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  mySPI.begin();
  delay(100);
  mySPI.beginTransaction(SPISettings(2000000000, MSBFIRST, SPI_MODE0)); //MSB first, according to the DAC spec

  pinMode(WS_pin, OUTPUT);
  aSin.setFreq(100);

  startMozzi(CONTROL_RATE);
  digitalWrite(LED, LOW);


}

void loop() {
    audioHook();
}

void updateControl() {}

AudioOutput_t updateAudio() {
return MonoOutput::from8Bit( aSin.next()).clip();
}
