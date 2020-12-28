# TES - 10 knobs synth
T. Combriat

10 knobs synths are simple synthesizers based on [Mozzi](https://github.com/sensorium/Mozzi) using STM32 blue pill with 10 knobs. Different versions are available:

  - 10knobs_mono_24bits_MCP4822 is a mono synth built around the MCP4822 dual DAC, with theoritical 24 bits resolution (in practice, around 14/16 bits get outside the noise, but that is already quite a lot).
  - 10knobs_stereo_16bits_PT8211 is a stereo synth built around the PT8211 dual DAC, with theoritical 16 bits resolution **on each channel**.


The aim of this serie is to provide a quite fixed hardware which can be used for different synthesis methods.


***

### Hardware
These synthesizers have: 
* MIDI input and thru
* 10 knobs for controlling parameters (thus the name), note that one is hardwired for logarithmic volume control
* 6.35mm analog (DAC) audio output (mono/stereo)
* standalone power from 3 AA batteries. This ensures cleaner sound thanks to very stable power lines.

PCBs for the chip are single faced and can be easily made if one is able to make 250 microns wide tracks. The mask is provided [here](8knobs_mono) for the mono version.

***

### Programming
These synths can be programmed like any other STM32 pills using USB to serial converter. Native USB will usually not work. You will  also need a rather new version of the Arduino IDE with Mozzi installed and modify Mozzi in accordance with the beginning of the sketch or use the [TES forked version of Mozzi](https://github.com/tomcombriat/Mozzi/tree/TES-stable).
