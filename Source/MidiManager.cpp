// **************************************************************************
//     Filename: MidiManager.cpp
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

#include "MidiManager.h"
#include <iostream>
using namespace std;


// **************************************************************************
// MidiManager
// **************************************************************************
MidiManager::MidiManager() {

    soundManager = nullptr;
    voiceManager = nullptr;
}

// **************************************************************************
// ~MidiManager
// **************************************************************************
MidiManager::~MidiManager() {

    soundManager = nullptr;
    voiceManager = nullptr;
}

// **************************************************************************
// reset
// **************************************************************************
void MidiManager::reset() {

    for (int n = 0; n < NUM_MIDI_NOTES; n++) {
        memset(&note[n], 0, sizeof(NOTE_STRUCTURE));
    }
}

// **************************************************************************
// initNote
// **************************************************************************
bool MidiManager::initNote(String cmdLine) {

StringArray fields;
int n, a, o;
int16_t soundNum;
String statMsg;
String soundFilePath;

    if (cmdLine.startsWith("#NOTE")) {
        fields.addTokens(cmdLine, ",", "");
        n = fields[1].getIntValue();
        if (n < NUM_MIDI_NOTES) {

            soundNum = fields[2].getIntValue();
            if (soundNum < MAX_SOUNDS_PER_BANK) {

                if ((a = note[n].numActions) < NUM_OUTPUTS) {
                    note[n].action[a].enabled = true;
                    note[n].action[a].soundIndex = soundNum;
                    for (o = 0; o < NUM_OUTPUTS; o++) {
                        note[n].action[a].gain_dB[o] = fields[3 + o].getFloatValue();
                    }
                    if (fields[11].getIntValue() != 0)
                        note[n].action[a].looping = true;
                    note[n].numActions++;
                }
            }
        }
    }

    return true;
}

// **************************************************************************
// noteOn
// **************************************************************************
void MidiManager::noteOn(uint8_t n, uint8_t v) {

int a;
SM_PLAY_STRUCTURE smp;

    if (n < NUM_MIDI_NOTES) {
        memset(&smp, 0, sizeof(SM_PLAY_STRUCTURE));
        for (a = 0; a < note[n].numActions; a++) {
            smp.snd[a].soundIndex = note[n].action[a].soundIndex;
            smp.snd[a].gain_dB = &note[n].action[a].gain_dB[0];
        }
        if (a > 0) {
            smp.numSounds = a;
            soundManager->playSounds(n, &smp);
        }
    }
}

// **************************************************************************
// noteOn
// **************************************************************************
void MidiManager::noteOff(uint8_t n) {

    voiceManager->stop(n);
}

