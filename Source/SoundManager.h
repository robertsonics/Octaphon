// **************************************************************************
//     Filename: SoundManager.h
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
#include "Sound.h"
#include "VoiceManager.h"

typedef struct {

    bool enabled;
    int16_t soundIndex;
    float gain_dB[NUM_OUTPUTS];

} SOUND_PLAY_STRUCTURE;

typedef struct {

    SOUND_PLAY_STRUCTURE snd[NUM_OUTPUTS];

} SM_PLAY_STRUCTURE;


// **************************************************************************
class SoundManager  {

public:
	SoundManager();
	~SoundManager();

	void setSoundPath(String sndPath)           { soundPath = sndPath; }
	bool loadSound(String cmdLine);
	void setVoiceManager(VoiceManager * vm)     { voiceManager = vm; }
	void reset();

	bool playSounds(uint8_t note, SM_PLAY_STRUCTURE * smp);

private:

    VoiceManager * voiceManager;

    String soundPath;
    Sound sound[MAX_SOUNDS_PER_BANK];

}; // end class SoundManager

