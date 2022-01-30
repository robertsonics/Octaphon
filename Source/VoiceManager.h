// **************************************************************************
//     Filename: VoiceManager.h
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

#include "Voice.h"
#include "DspUtils.h"

#define NUM_VOICES      POLYPHONY

// Our voice state definitions
enum {
    VOICE_STATE_EMPTY = 0,
    VOICE_STATE_READY,
    VOICE_STATE_PLAYING,
    VOICE_STATE_STOPPED
};

// The following structure is used to pass performance data to the voice
//  manager to start sounds

typedef struct {

    VOICE_PLAY_STRUCTURE vp[NUM_OUTPUTS];

} VM_PLAY_STRUCTURE;


// **************************************************************************
class VoiceManager {

public:
	VoiceManager();
	~VoiceManager();
	void setDspUtils(DspUtils * gu);

	int allocateVoice();
	int getActiveVoices()                           { return activeVoices; }
	bool play(VM_PLAY_STRUCTURE * ps);
	void stop(uint8_t midiNote);
    void getFrames(AudioBuffer<float> * mixBuff, uint16_t reqFrame);

private:

    // Our array of voices
    Voice * voice[NUM_VOICES];

    DspUtils * dspUtils;

	int activeVoices;

}; // end class VoiceManager

