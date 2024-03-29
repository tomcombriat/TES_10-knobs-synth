# TES - 10 knobs synth
T. Combriat 

10 knobs synths are simple synthesizers based on [Mozzi](https://github.com/sensorium/Mozzi) using STM32 blue pill with 10 knobs. Different versions are available:

  - 10knobs_mono_24bits_MCP4822 is a mono synth built around the MCP4822 dual DAC, with theoritical 24 bits resolution (in practice, around 14/16 bits get outside the noise, but that is already quite a lot). It can easily be turned into a stereo synth with 12bits on each channel.
  - 10knobs_mono_16bits_PT8211 is a mono synth built around the PT8211 dual DAC, with theoritical 16 bits resolution. This one can easily be upgraded to a stereo version: only one channel of the PT8211 is used here.


The aim of this serie is to provide a quite fixed hardware which can be used for different synthesis methods.


***

### Hardware
These synthesizers have: 
* MIDI input and thru
* 10 knobs for controlling parameters (thus the name), note that one is hardwired for logarithmic volume control
* 6.35mm analog (DAC) audio output (mono/stereo)
* standalone power from ~~3~~ 4 AA batteries. This ensures cleaner sound thanks to very stable power lines. This has been changed from 3 to 4 in order to get some room over the signal level for the op-amps.

PCBs for the chip are single faced and can be easily made if one is able to make 220 microns wide tracks. The masks are provided in the hardware folders for each version.

***

### Programming
These synths can be programmed like any other STM32 pills using USB to serial converter. Native USB will usually not work. You will  also need a rather new version of the Arduino IDE with Mozzi installed and modify Mozzi in accordance with the beginning of the sketch or use the [TES forked version of Mozzi](https://github.com/tomcombriat/Mozzi/tree/TES-stable).

As a general matter, the programs tries to use the most of the chip, so it usually needs to be compiled with -O2 or -O3 with the maximum overclock. As the chip is not confined, the OC does not pose any problem.
