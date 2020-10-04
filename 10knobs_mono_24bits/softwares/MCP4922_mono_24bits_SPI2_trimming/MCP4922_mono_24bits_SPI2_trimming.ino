/*  Trimming of the 24 bits dual dac.
 *   Should give a straigh saw line on the scope.

    #define EXTERNAL_AUDIO_OUTPUT true should be uncommented in mozzi_config.h.


    Circuit: (see the DAC library README for details)

    MCP4921   //  Connect to:
    -------       -----------
    Vdd           V+
    CS            any digital pin defined by SS_PIN (see after), or pin 7 on UNO / 38 on Mega if you are using Portwrite
    SCK           SCK of Arduino
    SDI           MOSI of Arduino
    VoutA/B       (see after)
    Vss           to GND
    VrefA/B       to V+ or a clean tension ref between V+ and GND
    LDAC          to GND


    Dual DAC electrical connections
    -------------------------------

    VoutA -------- R1 -----------> To headphones/loudspeaker or anything else
                            |
    VoutB -------- R2 -------

    R2 = 2^n * R1  with n the number of bits per stage.
    This should be precise, use a trimmer on R1 to adjust it precisely.
    Recommended values: R1 around 1k
                        R2 around 4M

   
    Mozzi documentation/API
    https://sensorium.github.io/Mozzi/doc/html/index.html

    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2012, CC by-nc-sa.
    T. Combriat 2020, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/cos2048_int8.h> // table for Oscils to play
#include <tables/saw8192_int8.h>
#include <SPI.h>
#include <DAC_MCP49xx.h>  // https://github.com/tomcombriat/DAC_MCP49XX 
// which is an adapted fork from https://github.com/exscape/electronics/tree/master/Arduino/Libraries/DAC_MCP49xx  (Thomas Backman)

#define CONTROL_RATE 256 // Hz, powers of 2 are most reliable


// Synthesis part
Oscil<SAW8192_NUM_CELLS, AUDIO_RATE> aSaw(SAW8192_DATA);



SPIClass mySPI(2);


// External audio output parameters and DAC declaration
#define SS_PIN PB12  // if you are on AVR and using PortWrite you need still need to put the pin you are actually using: 7 on Uno, 38 on Mega
#define AUDIO_BIAS 8388608  // we are at 24 bits, so we have to bias the signal of 2^(24-1) = 8388608
#define BITS_PER_CHANNEL 12  // each channel of the DAC is outputting 12 bits
DAC_MCP49xx dac(DAC_MCP49xx::MCP4922, SS_PIN);



void audioOutput(int l, int r)
{

  l += AUDIO_BIAS;

  unsigned short lowBits = (unsigned short) l;
  unsigned short highBits =  l >> BITS_PER_CHANNEL;

  dac.output2(lowBits, highBits);  // outputs the two channels in one call.
}



void setup() {
  aSaw.setFreq(500.f);
  dac.init(&mySPI);   // start SPI communications

  //dac.setPortWrite(true);  //comment this line if you do not want to use PortWrite (for non-AVR platforms)
Serial.begin(115200);
  startMozzi(CONTROL_RATE);
}





void updateControl() {
//Serial.println((aSaw.next()<< 4 ) - (1 << 22 ) + AUDIO_BIAS );
}


int updateAudio() {
  return ((aSaw.next()<< 8 )) ;  //should give a good saw line 
}


void loop() {
  audioHook();
}
