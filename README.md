# TES - 10 knobs synth
T. Combriat

10 knobs synths are simple synthesizers based on [Mozzi](https://github.com/sensorium/Mozzi) using STM32 blue pill and a dual DAC MCP4822. Thanks to the computing power of these chips, these synthesizers are able to generate complex polyphonic sounds at 32kHz sampling rate and theoritical 24 bits resolution (in practice, around 14/16 bits get outside the noise, but that is already quite a lot). The aim of this serie is to provide a fixed hardware which can be used for different synthesis methods.


***

### Hardware
These synthesizers have: 
* MIDI input and thru
* 10 knobs for controlling parameters (thus the name), note that one is hardwired for logarithmic volume control
* 6.35mm audio output (mono)
* standalone power from 3 AA batteries. This ensures cleaner sound thanks to very stable power lines.

PCBs for the chip are single faced and can be easily made if one is able to make 250 microns wide tracks. The mask is provided [here](8knobs_mono) for the mono version.

***

### Programming
These synths can be programmed like any other STM32 pills using USB to serial converter. Native USB will usually not work. You will  also need a rather new version of the Arduino IDE with Mozzi installed and modify Mozzi in accordance with the beginning of the sketch or use the [TES forked version of Mozzi](https://github.com/tomcombriat/Mozzi/tree/TES-stable).
