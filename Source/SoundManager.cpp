// **************************************************************************
//     Filename: SoundManager.cpp
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

#include "SoundManager.h"
#include <iostream>
using namespace std;


// **************************************************************************
// SoundManager
// **************************************************************************
SoundManager::SoundManager() {

    soundPath.clear();
    voiceManager = nullptr;
}

// **************************************************************************
// ~SoundManager
// **************************************************************************
SoundManager::~SoundManager() {

    voiceManager = nullptr;
}



// **************************************************************************
// init
// **************************************************************************
bool SoundManager::loadSound(String cmdLine) {

StringArray fields;
int soundIndex;
String statMsg;
String soundFilePath;

    if (cmdLine.startsWith("#FILE")) {
        fields.addTokens(cmdLine, ",", "");
        soundIndex = fields[1].getIntValue();
        if (soundIndex < MAX_SOUNDS_PER_BANK) {
            statMsg.clear();
            statMsg += "Sound ";
            statMsg += soundIndex;
            statMsg += " ";
            soundFilePath.clear();
            soundFilePath = soundPath + fields[2];
            statMsg += soundFilePath;
            if (sound[soundIndex].load(soundFilePath)) {
                statMsg += ", loaded";
            }
            else {
                statMsg += ", *** not loaded ***";
            }
            cout << statMsg << endl;
        }
    }
    return true;
}

// **************************************************************************
// reset
// **************************************************************************
void SoundManager::reset() {

}

// **************************************************************************
// reset
// **************************************************************************
bool SoundManager::playSounds(uint8_t note, SM_PLAY_STRUCTURE * smp) {

VM_PLAY_STRUCTURE vmp;
int n;
uint16_t s;

    memset(&vmp, 0, sizeof(VM_PLAY_STRUCTURE));
    for (n = 0; n < NUM_OUTPUTS; n++) {
        s = smp->snd[n].soundIndex;
        if (sound[s].exists()) {
            vmp.vp[n].enabled = true;
            vmp.vp[n].midiNote = note;
            vmp.vp[n].soundIndex = s;
            vmp.vp[n].pSoundBase = sound[s].getSoundBase();
            vmp.vp[n].numSamples = sound[s].getNumSamples();
            vmp.vp[n].gain_dB = smp->snd[n].gain_dB;
        }
    }
    voiceManager->play(&vmp);
    return true;
}

