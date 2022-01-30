// **************************************************************************
//     Filename: MidiManager.h
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

#pragma once

#include <JuceHeader.h>
#include "SoundManager.h"
#include "VoiceManager.h"

typedef struct {

    bool enabled;
    bool looping;
    int16_t soundIndex;
    float pitchOffset;
    float gain_dB[NUM_OUTPUTS];

} NOTE_ACTION_STRUCTURE;

typedef struct {

    uint16_t numActions;
    NOTE_ACTION_STRUCTURE action[NUM_OUTPUTS];

} NOTE_STRUCTURE;

// **************************************************************************
class MidiManager  {

public:
	MidiManager();
	~MidiManager();

	void setSoundManager(SoundManager * sm)     { soundManager = sm; }
	void setVoiceManager(VoiceManager * vm)     { voiceManager = vm; }
	void reset();
	bool initNote(String cmdLine);
	void noteOn(uint8_t n, uint8_t v);
	void noteOff(uint8_t n);

private:

    SoundManager * soundManager;
    VoiceManager * voiceManager;

    NOTE_STRUCTURE note[NUM_MIDI_NOTES];

}; // end class MidiManager

