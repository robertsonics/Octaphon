// **************************************************************************
//     Filename: Config.h
// Date Created: 1/23/2022
//
// This module is part of the Robertsonics Octaphon project
//
// COPYRIGHT (c) 2022 Robertsonics
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// **************************************************************************
//
// This file contains global defines that we are likely to want to change to
//  configure the system

#pragma once

// Graphical user interface defines

#define MY_BG_COLOUR            Colour(0xff121212)
#define MY_TAB_COLOUR           Colour(0xff252525)
#define MY_BUTTON_COLOUR        Colours::royalblue
#define MY_TEXT_COLOUR          Colours::skyblue
#define MY_KNOB_COLOUR          Colours::springgreen
#define MY_ALARM_COLOUR         Colour(0xffb45ba0)

#define QWIIC_ADDRESS           0x28

#define MAX_SOUNDS_PER_BANK     128

#define SAMPLE_RATE             44100

#define POLYPHONY		        24

#define NUM_OUTPUTS             8

#define MIN_GAIN_DB             -100.0

#define NUM_MIDI_NOTES          128

// The alsa period is the number of frames that we'll transfer to the sound
//  driver at each "interrupt". For alsa purposes, we're treating it as stereo,
//  since the data will get clocked out as I2S. But since we're really sending
//  4 stereo pairs sequentially at 4X the sample rate, we need to make the buffer
//  4 times as large.
#define ALSA_PERIOD_FRAMES      1024
#define ALSA_PERIODS            3

// Number of microseconds between checking for alsa updates
#define ALSA_UPDATE_INTERVAL    500

// Number of microseconds between checking voices for read requests
#define READER_UPDATE_INTERVAL  1000

#define UNITY_PITCH_INC         0x00010000

// Helper types for dealing with endiness

typedef union {
	uint32_t u32;
	uint16_t u16[2];
	uint8_t u8[4];
} U32_UNION;


