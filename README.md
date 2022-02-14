Octaphon Polyphonic Multi-Channel Audio Player
==============================================

This software implements a polyphonic, multi-channel audio player on the Raspberry Pi. Its
purpose is to trigger asynchronous audio events with low latency from a variety of trigger
sources, including MIDI, serial and ethernet. It is intended to be used for custom performance
musical instruments, interactive art installation, museum exhibits, pinball machines, etc.
It is not streamer softare.

If you're familiar with my embedded products on SparkFun, it is most like the Tsunami. Being
hosted by a Raspberry Pi, however, means it has more speed, more memory and more control
interface capabilities. Unlike Tsunami, MIDI Notes can trigger multiple sounds, and each
sound can have individual pitch offset and be sent in any combination to any or all of the
audio outputs.

Octaphon is being developed in conjuction with a custom Raspberry Pi multi-channel audio HAT.

https://robertsonics.com/2022/02/10/multi-channel-audio-for-the-rasperry-pi-part-2-the-octaphon-project/

This HAT uses the RPi I2S and I2C ports on the RPi GPIO header to provide 8 channels of output
(as well as 2 channels of input, not currently used by this software.) Because I do not curr-
ently have official linux Alsa ASoC drivers for this HAT, the Octaphon software contains some
dedicated code in the Mixer module to utilize 8 channels of output. Using a custom device tree
overlay file, the HAT presents to linux as a stereo board, and the mixer module uses standard
Alsa API functions to manage and play audio. But the HAT drives the I2S clocks at 4X the audio
sample rate, while the mixer multiplexes 4 sets of stereo channels into the output buffers, and
a novel mechanism implemented in both the mixer and the HAT firmware keep the channel assign-
ments correct.

Because the mixer code uses Alsa functions, it would be relatively straightforward to modify
Octaphon to support standard stereo HATs as well as other multichannel interfaces such as
XMOS based USB Audio 2.0 devices.

Unlike the WAV Trigger and Tsunami, Octaphon loads sets of up to 128 sound files into RAM. This
is done both on startup and also can be done at runtime to change the sound selection. Because
of this, Octaphon will support looping over a specified address range, which need not be the
beginning and end of the file.

#### Current Capabilites

Octaphon is intended to be run headless as an embedded audio player. I've implemented a GUI
intended to be displayed on an 800X480 GUI LED panel, showing signal level on 8 outputs as
well as timing/performance information. Of course, it also displays fine on a standard
desktop used for development.

At present, Octaphon implements a MIDI interface to trigger sounds. The MIDI input devices
are enumerated and presented in a drop-down combo box and can be selected from the GUI.

An Excel-generated csv file is used to define a set of sound files to be loaded as well as
function definitions for MIDI Note events.

#### Things to do:

#### Building Octaphon

Octaphon is written for linux in C++ using the Juce framework. For ease of development, I have
Juce installed on a full desktop version of the Raspberry Pi OS, along with the Code::Blocks
IDE. I have two exporters defined in the Octaphon.jucer project - one for Code::Blocks and one
for the linux command line make.

To begin using just the linux command line, first install Juce, then the required linux packages.
Build the Projucer and then open the Octaphon.jucer in Projucer. Save the project, then open
a terminal to the resulting /Builds/LinuxMakefile folder and just type make. If you also have
Code::Blocks installed you can navigate to the /Builds/CodeBlocksLinux folder, open the project
and build from within CodeBlocks.

#### Running Octaphon

The build creates a single executable which can be from the command line


**wTrig.start()** - you must call this method first to initialize the serial
  communications.



  